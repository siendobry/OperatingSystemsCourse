#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <dlfcn.h>
#include <sys/times.h>
#include <time.h>
#include "../zad1/wclib.h"


int main() {


#ifdef DYNAMIC
    void *handle = dlopen("../zad1/libwclib.so", RTLD_LAZY);
    if (handle == NULL) {
        puts("An error has occured while loading the shared library!");
        return 3;
    }

    struct BlockStorage (*create_storage)(int) = dlsym(handle, "create_storage");
    int (*alloc_table)(struct BlockStorage*, int) = dlsym(handle, "alloc_table");
    bool (*does_storage_exist)(struct BlockStorage*) = dlsym(handle, "does_storage_exist");
    int (*eval_wc)(struct BlockStorage*, char*) = dlsym(handle, "eval_wc");
    char *(*get_block)(struct BlockStorage*, int) = dlsym(handle, "get_block");
    int (*delete_block)(struct BlockStorage*, int) = dlsym(handle, "delete_block");
    void (*clear_storage)(struct BlockStorage*) = dlsym(handle, "clear_storage");
#endif


    char *buffer;
    int buffer_size = 32;
    char *command;
    char *arg;
    bool has_arg;

    struct tms tms_start;
    struct tms tms_end;
    clock_t tms_result;

    struct timespec timespec_start;
    struct timespec timespec_end;
    int timespec_result;

    struct BlockStorage storage = create_storage(0);
    buffer = (char *) malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        puts("Could not allocate buffer");
        return 2;
    }

    fputs("> ", stdout);
    fgets(buffer, buffer_size, stdin);
    command = strtok(buffer, " ");
    arg = strtok(NULL, " ");

    while (strncmp(command, "exit", 4) != 0) {
        tms_result = times(&tms_start);
        if (tms_result == -1) {
            puts("An error has occurred while getting time information (tms).");
            return 4;
        }

        timespec_result = clock_gettime(CLOCK_REALTIME, &timespec_start);
        if (timespec_result == -1) {
            puts("An error has occurred while getting time information (timespec).");
            return 4;
        }


        if (command == NULL) {
            puts("Incorrect command!");
            fputs("> ", stdout);
            fgets(buffer, buffer_size, stdin);
            command = strtok(buffer, " ");
            arg = strtok(NULL, " ");
            continue;
        }

        if (arg == NULL) {
            has_arg = false;
        }
        else {
            has_arg = true;
        }


        if (!strncmp(command, "init", 4) && has_arg) {
            if (does_storage_exist(&storage)) {
                puts("Storage already exists!");
                puts("In order to allocate a storage of a different size, delete already existing one first.");
            }
            long size = strtol(arg, NULL, 10);
            if (size == LONG_MAX || size == LONG_MIN) {
                puts("Incorrect argument!");
                return 1;
            }
            int alloc_result = alloc_table(&storage, (int) size);
            if (alloc_result) {
                return alloc_result;
            }
        }
        else if (!strncmp(command, "count", 5) && has_arg) {
            arg[strcspn(arg, "\n")] = 0;
            int eval_result = eval_wc(&storage, arg);
            if (eval_result) {
                return eval_result;
            }
        }
        else if (!strncmp(command, "show", 4) && has_arg) {
            long idx = strtol(arg, NULL, 10);
            if (idx == LONG_MAX || idx == LONG_MIN) {
                puts("Incorrect argument!");
                return 1;
            }
            char *get_result = get_block(&storage, (int) idx);
            if (get_result == NULL) {
                return 1;
            }
            fputs(get_result, stdout);
        }
        else if (!strncmp(command, "delete", 6) && has_arg) {
            long idx = strtol(arg, NULL, 10);
            if (idx == LONG_MAX || idx == LONG_MIN) {
                puts("Incorrect argument!");
                return 1;
            }
            int delete_result = delete_block(&storage, (int) idx);
            if (delete_result) {
                return delete_result;
            }
        }
        else if (!strncmp(command, "destroy", 7) && !has_arg) {
            if (!does_storage_exist(&storage)) {
                puts("Storage does not exist!");
            }
            else {
                clear_storage(&storage);
            }
        }
        else {
            puts("Incorrect command!");
        }


        tms_result = times(&tms_end);
        if (tms_result == -1) {
            puts("An error has occurred while getting time information.");
            return 4;
        }

        timespec_result = clock_gettime(CLOCK_REALTIME, &timespec_end);
        if (timespec_result == -1) {
            puts("An error has occurred while getting time information (timespec).");
            return 4;
        }

        printf("Real time: %f\n", timespec_end.tv_sec - timespec_start.tv_sec + (timespec_end.tv_nsec - timespec_start.tv_nsec) / (1e9));
        printf("CPU time in user mode: %f\n", (double) (tms_end.tms_utime - tms_start.tms_utime) / CLOCKS_PER_SEC);
        printf("CPU time in system mode: %f\n", (double) (tms_end.tms_stime - tms_start.tms_stime) / CLOCKS_PER_SEC);


        fputs("> ", stdout);
        fgets(buffer, buffer_size, stdin);
        command = strtok(buffer, " ");
        arg = strtok(NULL, " ");

    }

    if (does_storage_exist(&storage)) {
        clear_storage(&storage);
    }
    free(buffer);


#ifdef DYNAMIC
    if (dlclose(handle) != 0) {
        puts("An error has occured while unloading the shared library!");
        return 3;
    }
#endif


    return 0;
}