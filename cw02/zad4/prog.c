#include <stdio.h>
#include <sys/stat.h>
#include <ftw.h>


long long sum_size = 0;

int print_size_name(
        const char *fpath,
        const struct stat *sb,
        int typeflag
    ) {
    if (typeflag != FTW_D) {
        sum_size += sb->st_size;
        printf("%ld %s\n", sb->st_size, fpath);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        puts("Incorrent amount of arguments passed.");
        return -1;
    }

    if (ftw(argv[1], print_size_name, 1) != 0) {
        puts("An error occurred while traversing file tree.");
        return 1;
    }
    printf("%lld total\n", sum_size);

    return 0;
}