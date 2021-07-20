/**
 * ls - list all files in given directory.
 */

#include <stdio.h>
#include <sys/dir.h>

/**
 * Print out all files in a directory. Return the number
 * of files listed.
 */
unsigned core_ls(DIR * dir) {

    struct dirent * entry;
    unsigned count = 0;

    while ((entry = readdir(dir)) != NULL) {

        if (entry->d_name[0] == '.') {
            continue; /* skip ".", "..", etc. */
        }

        printf("%s", entry->d_name);
        ++count;

        if (entry->d_type & DT_DIR) {
            printf("/"); /* directory marker - forward slash */
        }

        printf("\n");

    }

    return count;

}

int main(int argc, char ** argv) {

    struct dirent entry;
    DIR         * dir;
    char        * path = "."; /* default to current directory */
    char        * ls   = argv[0];
    int           has_path = 0; /* has path been specified? */

    --argc, ++argv; /* skip program name */
    
    while (argc) {
        if (argv[0][0] == '-') {
            fprintf(stderr, "%s: No flags supported for now.\n", ls);
            return 1;
        } else {
            if (has_path) {
                fprintf(stderr, "%s: Only one path allowed.\n", ls);
                return 1;
            } else {
                path = argv[0];
                has_path = 1;
            }
        }
        --argc, ++argv;
    }

    dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "%s: %s: No such directory.\n", ls, path);
        return 1;
    }

    core_ls(dir);

    return 0;

}
