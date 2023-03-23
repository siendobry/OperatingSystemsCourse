#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "prog.h"


int process_single_file(char *filepath, char *regex) {
    if (strlen(filepath) > PATH_MAX) {
        perror("Path to file too long");
        return 1;
    }

    struct stat st;
    int stat_result = stat(filepath, &st);
    if (stat_result == -1) {
        perror("Could not get file's info");
        return 1;
    }
    if (S_ISDIR(st.st_mode) && fork() == 0) {
        if (process_directory(filepath, regex) != 0) {
            perror("An error occurred while processing a directory");
            return 1;
        }
    }

    else {
        size_t regex_length = strlen(regex);

        FILE *file = fopen(filepath, "r");
        if (file == NULL) {
            perror("Could not open a file");
            return 1;
        }

        char *buffer = calloc(sizeof(char), regex_length);
        if (buffer == NULL) {
            perror("Could not allocate memory");
            return 1;
        }

        size_t read_result = fread(buffer, sizeof(char), regex_length, file);
        if (read_result == -1) {
            perror("Could not read from a file");
            return 1;
        }
        if (fclose(file) == -1) {
            perror("Could not close a file");
            return 1;
        }

        if (strcmp(buffer, regex) == 0) {
            printf("%s %d\n", filepath, getpid());
        }

        free(buffer);
    }
    free(filepath);

    return 0;
}

int process_directory(char *filepath, char *regex) {
    DIR *dirp = opendir(filepath);
    if (dirp == NULL) {
        perror("Could not open given directory");
        return 1;
    }

    for (struct dirent *file = readdir(dirp); file != NULL; file = readdir(dirp)) {
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            continue;
        }
        char *child_filepath = calloc(sizeof(char), strlen(filepath) + strlen(file->d_name) + 2);
        strcpy(child_filepath, filepath);
        strcat(child_filepath, "/");
        strcat(child_filepath, file->d_name);
        if (process_single_file(child_filepath, regex) != 0) {
            perror("An error occurred while processing a file");
            return 1;
        }
    }

    if (closedir(dirp) == -1) {
        perror("Could not close a directory");
        return 1;
    }

    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        puts("Invalid number of arguments");
        return -1;
    }
    size_t regex_length = strlen(argv[2]);
    if (regex_length > 255) {
        puts("Second argument' length must fit in between 0 and 255");
        return -1;
    }

    argv[2][regex_length] = 0;
    process_directory(argv[1], argv[2]);

    return 0;
}