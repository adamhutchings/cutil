#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int max = 10;
    int increment = 0;

    if (argc < 2) {
        printf("head needs one file as an argument");
        exit(EXIT_FAILURE);
    }

    if (argc > 3) {
        // Check if the -n flag was given
        if (!strcmp(argv[2], "-n")) {
            // Convert the arg after -n to an integer and use it as the max
            max = atoi(argv[3]);
        } else {
            printf("wrong argument supplied '%s'", argv[2]);
            exit(EXIT_FAILURE);
        }
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    // Check if it's reached the max line limit and if there are still more
    // lines to print
    while (increment < max && getline(&line, &len, fp) != -1) {
        printf("%s",line);
        increment++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
