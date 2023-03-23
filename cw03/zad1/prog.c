#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Invalid number of arguments. Only one argument should be inputted.");
        return -1;
    }

    long n = strtol(argv[1], NULL, 10);
    if ((!strcmp(argv[1], "0") && n == 0) || n == LONG_MAX || n == LONG_MIN) {
        perror("Could not convert input argument to an arithmetic type.");
        return 1;
    }
    for (long i = 0; i < n; ++i) {
        int child_pid = fork();
        if (child_pid != 0) {
            continue;
        }
        else {
            printf("%d %d\n", getppid(), getpid());
            return 0;
        }
    }

    int child_status = wait(NULL);
    while (child_status != -1) {
        child_status = wait(NULL);
    }
    printf("%d %d\n", getppid(), getpid());

//    for (long i = 0; i < n; ++i) {
//        int child_pid = fork();
//        if (child_pid != 0) {
//            wait(NULL);
//            printf("%d %d\n", getppid(), getpid());
//            return 0;
//        }
//    }
//    printf("%d %d\n", getppid(), getpid());

    return 0;
}