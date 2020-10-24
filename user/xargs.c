#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
	char *argv_n[MAXARG];
	int i = 1;
	for(;i<argc;i++) {
		argv_n[i-1] = argv[i];
	}

	int off = 0;
	while(argv[2][off]) {
		off++;
	}

  char c;
	i = 0;
  while(read(0, &c, sizeof(char))) {
		if(c == '\n') {
			int pid = fork();
		  if(pid == 0) {
     		exec(argv_n[0], argv_n);
   		} else if (pid > 0) {
     		wait(0);
   		} else {
     		fprintf(2, "fork error");
   		}
		} else {
			memcpy(argv_n[1] + off + i, &c, 1);
			i++;
		}
  }
  exit(0);
} 
