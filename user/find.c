#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *file, int depth) {
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type) {
  case T_FILE:
    //printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }
			if(strcmp(de.name, ".") && strcmp(de.name, "..")) {
				switch(st.type) {
					case T_FILE:
						if(!strcmp(de.name, file)) {
							if(depth > 1) {
								printf("./");
							}
							printf("%s\n", buf);
						}
						break;
					case T_DIR:
						if(depth > 1) {
							find(buf, file, depth+1);
						} else {
							find(de.name, file, depth+1);
						}
						break;
				}
			}
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		fprintf(2, "error: invalid arguments; usage: find <where> <what>\n");
		exit(-1);
	}

	find(argv[1], argv[2], 1);

  exit(0);
}
