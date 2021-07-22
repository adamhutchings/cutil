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
        if (!strcmp(argv[2], "-n")) {
            max = atoi(argv[3]);
        }
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    while (increment < max) {
        getline(&line, &len, fp);
        printf("%s",line);
        increment++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
