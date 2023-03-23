#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "wclib.h"


struct BlockStorage create_storage(int size) {
    struct BlockStorage storage;
    alloc_table(&storage, size);
    return storage;
}

int alloc_table(struct BlockStorage *storage, int size) {
    if (size < 1) {
        storage->blocks = NULL;
        storage->max_size = 0;
    }
    else {
        storage->blocks = (char**) calloc(size, sizeof(char*));
        if (storage->blocks == NULL) {
            puts("Could not allocate memory!");
            return 8;
        }
        storage->max_size = size;
    }
    storage->current_size = 0;
    return 0;
}

bool does_storage_exist(struct BlockStorage *storage) {
    if (storage->blocks != NULL) {
        return true;
    }
    return false;
}

int eval_wc(struct BlockStorage *storage, char *filename) {
    if (storage->current_size == storage->max_size) {
        puts("Storage is full!");
        return 1;
    }
    char name[] = "/tmp/fileXXXXXX";
    int fd = mkstemp(name);
    unlink(name);
    if (fd == -1) {
        puts("Unable to create temp file!");
        return 2;
    };
    int filename_size = strlen(filename);
    char *command = malloc((23 + filename_size)* sizeof(char));
    strcpy(command, "wc ");
    char tmp_filename[filename_size];
    strcpy(tmp_filename, filename);
    strcat(command, tmp_filename);
    strcat(command, " > ");
    strcat(command, name);
    int success = system(command);
    if (success != 0) {
        puts("Unable to evaluate wc command!");
        return 3;
    }
    struct stat st;
    int stat_result = stat(name, &st);
    if (stat_result != 0) {
        puts("Error while reading tmp file size!");
        return 4;
    }
    size_t tmp_size = st.st_size;
    for (int i = 0; i < storage->max_size; ++i) {
        if (storage->blocks[i]) {
            continue;
        }
        storage->blocks[i] = (char*) calloc(1, tmp_size);
        FILE *tmp_file = fopen(name, "r");
        size_t read_bytes = fread(storage->blocks[i], 1, tmp_size, tmp_file);
        int close_result = fclose(tmp_file);
        if (read_bytes != tmp_size) {
            puts("Error while reading tmp file!");
            return 5;
        }
        if (close_result != 0) {
            puts("Error while closing tmp file!");
            return 6;
        }
        break;
    }
    storage->current_size = storage->current_size + 1;
    char rm_tmp_command[19] = "rm ";
    strcat(rm_tmp_command, name);
    int rm_result = system(rm_tmp_command);
    if (rm_result != 0) {
        puts("Error while removing tmp file!");
        return 7;
    }
    return 0;
};

char *get_block(struct BlockStorage *storage, int idx) {
    if (!storage->blocks[idx]) {
        puts("Nothing to return at a given index!");
        return NULL;
    }
    return storage->blocks[idx];
}

int delete_block(struct BlockStorage *storage, int idx) {
    if (!storage->blocks[idx]) {
        puts("Nothing to delete at a given index!");
        return 7;
    }
    free(storage->blocks[idx]);
    storage->blocks[idx] = NULL;
    storage->current_size = storage->current_size - 1;
    return 0;
}

void clear_storage(struct BlockStorage *storage) {
    for (int i = 0; i < storage->max_size; ++i) {
        if (!storage->blocks[i]) {
            continue;
        }
        free(storage->blocks[i]);
    }
    free(storage->blocks);
    storage->blocks = NULL;
}