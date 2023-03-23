#include <stdio.h>
#include "wclib.h"

int main() {
    struct BlockStorage storage = create_storage(2);
    int eval_res1 = eval_wc(&storage, "test1.txt");
    if (eval_res1 != 0) {return eval_res1;}
    puts(get_block(&storage, 0));
    int eval_res2 = eval_wc(&storage, "test2.txt");
    if (eval_res2 != 0) {return eval_res2;}
    puts(get_block(&storage, 1));
    int delete_res = delete_block(&storage, 1);
    if (delete_res != 0) {return delete_res;}
    int eval_res3 = eval_wc(&storage, "test1.txt");
    if (eval_res3 != 0) {return eval_res3;}
    puts(get_block(&storage, 1));
    clear_storage(&storage);
    return 0;
}