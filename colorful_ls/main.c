#define _DEFAULT_SOURCE
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static inline void print_red(const char *s) {
    printf("\33[0;31m%s\33[0m\n", s);
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *dp;
    if (argc == 1) {
        char buf[128];
        if (getcwd(buf, 128) == NULL) {
            exit(1);
        }
        dir = opendir(buf);
        if (dir == NULL) {
            exit(1);
        }
        while (dp = readdir(dir)) {
            if (dp->d_type == DT_DIR) {
                print_red(dp->d_name);
            } else {
                printf("%s\n", dp->d_name);
            }
        }
    } else if (argc == 2) {
        struct stat buf;
        if (stat(argv[1], &buf) != 0) {
            printf("%s: cannot access '%s': No such file or directory\n", argv[0], argv[1]);
            exit(1);
        }
        if (S_ISDIR(buf.st_mode)) {
            dir = opendir(argv[1]);
            if (dir == NULL) {
                exit(1);
            }
            while (dp = readdir(dir)) {
                if (dp->d_type == DT_DIR) {
                    print_red(dp->d_name);
                } else {
                    printf("%s\n", dp->d_name);
                }
            }
        } else {
            printf("%s\n", argv[1]);
        }
    }

    return 0;
}