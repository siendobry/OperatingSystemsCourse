#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]) {
    clock_t start_time = clock();

    if (argc != 3) {
        puts("Incorrect amount of arguments passed.");
        return -1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];
    int input_file = open(input_filename, O_RDONLY);
    if (input_file == -1) {
        puts("Could not open an input file.");
        return 1;
    }
    int output_file = open(output_filename, O_WRONLY);
    if (output_file == -1) {
        puts("Could not open an output file.");
        return 1;
    }

    struct stat st;
    fstat(input_file, &st);
    size_t input_file_size = st.st_size;
    char *buffer = calloc(sizeof(char), sizeof(char) * input_file_size);
    if (buffer == NULL) {
        puts("Could not allocate memory for buffer.");
        return 3;
    }
    for (int i = 0; i < input_file_size; ++i) {
        off_t lseek_result = lseek(input_file, -(i + 1), SEEK_END);
        if (lseek_result == -1) {
            puts("An error occurred while performing lseek operation.");
            return 2;
        }
        size_t bytes_read = read(input_file, buffer + i, sizeof(char));
        if (bytes_read != sizeof(char)) {
            puts("An error occurred while reading from an input file.");
            return 2;
        }
    }

    size_t bytes_written = write(output_file, buffer, sizeof(char) * input_file_size);
    free(buffer);
    if (bytes_written != sizeof(char) * input_file_size) {
        puts("An error occurred while writing to an input file.");
        return 2;
    }

    if (close(input_file) == -1) {
        puts("Could not close an input file.");
        return 1;
    }
    if (close(output_file) == -1) {
        puts("Could not close an output file.");
        return 1;
    }

    clock_t end_time = clock();
    printf("%f\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
    return 0;
}