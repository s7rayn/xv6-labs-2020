#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child(int fd) {
  int p, n;
  int write_fd[2];
  int no_child = 1;
  pipe(write_fd);

  if(read(fd, &p, sizeof(int)) != sizeof(int))
		exit(-1);

  printf("prime %d\n", p);

  while (read(fd, &n, sizeof(int)) == sizeof(int)) {
    if ((n % p) != 0) {
      if (no_child) {
        no_child = 0;
        int pid = fork();
        if (pid == 0) { // child
            close(write_fd[1]); // zavri zapisovaci deskriptor
            child(write_fd[0]); // zavolaj znova na citaci deskriptor
            break;
        } else if (pid < 0) {
            fprintf(2, "error: fork failed\n");
        }
      }
      write(write_fd[1], &n, sizeof(int));
    }
  }
  close(write_fd[1]);
  wait(0);
}

int main() {
  int fds[2];
  close(0); // zatvor standard input

  pipe(fds);

  int pid = fork();

  if (pid == 0) { // child
    close(fds[1]); // dieta nebude do pipe zapisovat
    child(fds[0]);
  } else if (pid > 0) { // parent
    for (int i = 2; i <= 35; i++) {
        write(fds[1], &i, sizeof(int));
    }
    close(fds[1]);
    wait(0);
  } else {
    fprintf(2, "error: fork failed\n");
  }
  exit(0);
}
