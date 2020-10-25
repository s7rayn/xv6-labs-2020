#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int parent[2];
    int child[2];

    pipe(parent);
    pipe(child);

    int pid = fork();

    if (pid == 0) { // child
        char c;
        read(parent[0], &c, 1);
        printf("%d: received pong\n", getpid());
        write(child[1], "x", sizeof(char));
    } else if (pid > 0) { //parent
        write(parent[1], "y", sizeof(char));
        char c;
        read(child[0], &c, 1);
        printf("%d: received ping\n", getpid());
    } else {
        fprintf(2, "error: fork failed");
    }

    exit(0);
}
