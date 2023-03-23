#include <stdbool.h>

#ifndef WCLIB_H
#define WCLIB_H


struct BlockStorage {
    int max_size;
    int current_size;
    char **blocks;
};

struct BlockStorage create_storage(int size);

int alloc_table(struct BlockStorage *storage, int size);

bool does_storage_exist(struct BlockStorage *storage);

int eval_wc(struct BlockStorage *storage, char *filename);

char *get_block(struct BlockStorage *storage, int idx);

int delete_block(struct BlockStorage *storage, int idx);

void clear_storage(struct BlockStorage *storage);


#endif