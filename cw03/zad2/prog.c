#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Invalid number of arguments.");
        return -1;
    }

    printf("%s ", argv[0]);
    fflush(stdout);
    int status = execl("/bin/ls", "ls", argv[1], NULL);
    if (status == -1) {
        perror("An exec function finished with an error code.");
        return 1;
    }

    return 0;
}