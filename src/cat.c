#include <stdio.h>

int main(int argc, char **argv) {
    FILE *fp;
    size_t len;
    char *line;

    // Check if enough args have been given
    // argv[1] will be read as the filename
    if (argc < 2) {
        printf("cat needs one file as an argument.\n");
        return 1;
    }

    // Open the file
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File does not exist.\n");
        return 1;
    }

    // Check if it's reached the max line limit and if there are still more
    // lines to print
    while (getline(&line, &len, fp) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
