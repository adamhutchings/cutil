#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int number = 1;

    if (argc < 2) {
        printf("nl needs one file as an argument");
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        printf("nl was given too many arguments");
        exit(EXIT_FAILURE);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp) != -1)) {
        // Check if the line is empty, don't print the
        // line or don't increment number
        if (line[0] == '\n') {
            printf("\n");
            continue;
        }

        printf("%6d  %s", number, line);
        number++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
