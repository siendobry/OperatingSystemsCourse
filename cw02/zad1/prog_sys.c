#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]) {
    clock_t start_time = clock();

    if (argc != 5) {
        puts("Incorrect amount of arguments passed.");
        return -1;
    }
    char to_be_replaced = argv[1][0];
    char replacement = argv[2][0];
    char *input_filename = argv[3];
    char *output_filename = argv[4];
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
    stat(input_filename, &st);
    size_t input_file_size = st.st_size;
    char *buffer = calloc(sizeof(char), input_file_size);
    if (buffer == NULL) {
        puts("Could not allocate memory for buffer.");
        return 3;
    }
    size_t bytes_read = read(input_file, buffer, sizeof(char) * input_file_size);
    if (bytes_read != input_file_size) {
        puts("An error occurred while reading from an input file.");
        return 2;
    }

    for (int i = 0; i < input_file_size; ++i) {
        if (buffer[i] == to_be_replaced) {
            buffer[i] = replacement;
        }
    }

    size_t bytes_written = write(output_file, buffer, sizeof(char) * input_file_size);
    free(buffer);
    if (bytes_written != input_file_size) {
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