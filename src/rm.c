/**
 * rm - remove a file, or recursively remove a directory and its contents.
 */

#include <stdio.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Remove a directory. Return number of files deleted.
 */
int rm_folder(char * path) {

    int             count;
    DIR           * dir;
    struct dirent * entry;
    
    /* Change directory to path */
    chdir(path);

    dir = opendir(".");
    if (dir == NULL) {
        return -1;
    }
    while ( (entry = readdir(dir)) != NULL) {

        if (entry->d_name[0] == '.') {
            /* Remove ALL directories, but not . and .. */
            if (entry->d_name[1] == '\0' || entry->d_name[1] == '.') {
                continue;
            }
        }

        /* Remove file */
        if (entry->d_type == DT_REG) {
            unlink(entry->d_name);
            ++count;
        } else if (entry->d_type == DT_DIR) {
            /* Recursively remove directory */
            count += rm_folder(entry->d_name);
        }

    }

    /* Change back */
    chdir("..");

    rmdir(path);

    return count;

}

int main(int argc, char **argv) {

    char          * rm = argv[0];
    char          * path;
    struct stat     pathstat;

    ++argv, --argc;

    if (argc == 0) {
        fprintf(stderr, "%s:\nUsage: rm [file]", rm);
        return 0;
    }

    if (argc > 1) {
        fprintf(stderr, "%s: only pass one directory or file.\n", rm);
        return 1;
    }

    path = argv[0];

    if (stat(path, &pathstat) != 0) {
        fprintf(stderr, "%s: %s: no such file or directory\n", rm, path);
        return 1;
    } else {
        if (S_ISDIR(pathstat.st_mode)) {
            rm_folder(path);
        } else {
            if (unlink(path) != 0) {
                fprintf(stderr, "%s: could not remove %s\n", rm, path);
                return 1;
            }
        }
    }
   
}
