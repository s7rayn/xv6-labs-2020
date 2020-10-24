#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
	int parent[2], child[2], pid;
	pipe(parent);
	pipe(child);
	
	pid = fork();
	
	if(pid == 0) { // child
		char received;
		int r = read(child[0], &received, 1);
		if(r == 1)
			printf("%d: received ping\n", getpid());
		write(parent[1], "y", 1);
	} else if(pid > 0) { // parent
		write(child[1], "x", 1);
		
		char received;
		int r = read(parent[0], &received, 1);
		
		if(r == 1)
			printf("%d: received pong\n", getpid());
	} else {
		fprintf(2, "fork error");
		exit(1);
	}
	exit(0);
}
