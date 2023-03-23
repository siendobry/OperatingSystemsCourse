#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
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
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        puts("Could not open an input file.");
        return 1;
    }
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
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
    size_t bytes_read = fread(buffer, sizeof(char), input_file_size, input_file);
    if (bytes_read != input_file_size) {
        puts("An error occurred while reading from an input file.");
        return 2;
    }

    for (int i = 0; i < input_file_size; ++i) {
        if (buffer[i] == to_be_replaced) {
            buffer[i] = replacement;
        }
    }

    size_t bytes_written = fwrite(buffer, sizeof(char), input_file_size, output_file);
    free(buffer);
    if (bytes_written != input_file_size) {
        puts("An error occurred while writing to an input file.");
        return 2;
    }

    if (fclose(input_file) != 0) {
        puts("Could not close an input file.");
        return 1;
    }
    if (fclose(output_file) != 0) {
        puts("Could not close an output file.");
        return 1;
    }

    clock_t end_time = clock();
    printf("%f\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
    return 0;
}