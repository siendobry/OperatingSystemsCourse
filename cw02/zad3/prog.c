#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>


int main() {
    DIR *dirp = opendir(".");
    if (dirp == NULL) {
        puts("Could not open the current directory.");
        return 1;
    }

    long long sum_size = 0;
    for(struct dirent *dir = readdir(dirp); dir != NULL; dir = readdir(dirp)) {
        struct stat st;
        stat(dir->d_name, &st);
        if (!S_ISDIR(st.st_mode)) {
            sum_size += st.st_size;
            printf("%ld %s\n", st.st_size, dir->d_name);
        }
    }
    printf("%lld total\n", sum_size);

    int close_result = closedir(dirp);
    if (close_result == -1) {
        puts("Could not close the current directory.");
        return 1;
    }
    return 0;
}