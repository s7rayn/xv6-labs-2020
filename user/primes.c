#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child(int fd) {
	int p, n, write_fd[2], no_child = 1;
	
	pipe(write_fd);

	read(fd, &p, sizeof(int));
 	printf("prime %d\n", p);

	while(read(fd, &n, sizeof(int)) == sizeof(int)) {
		if((n % p) != 0) {
			if(no_child) {
				no_child = 0;
				int pid = fork();
				if(pid == 0) {
					close(write_fd[1]);
					child(write_fd[0]);
					break;
				} else if (pid < 0) {
					fprintf(2, "fork error");
				}
			}
			write(write_fd[1], &n, sizeof(int));
		}
	}
	close(write_fd[1]);
	wait(0);
}

int main() {
	int fd[2];
	close(0);

	pipe(fd);
	int pid = fork();

	if(pid == 0) {
		// child
		close(fd[1]);
		child(fd[0]);
	} else if(pid > 0) {
		//parent
		for(int i=2;i<=35;i++) {
			write(fd[1], &i, sizeof(int));
		}
		close(fd[1]);
		wait(0);
	} else {
		fprintf(2, "fork error");
	}

	exit(0);
}
