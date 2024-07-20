#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h> 

#define VERSION "v1.0"

void print_version() {
    printf("cdf %s\n", VERSION);
}

void print_help() {
    printf("Usage: cdf [OPTION] [DIRECTORY/FILE]\n");
    printf("Options:\n");
    printf("  --version    - Print version information\n");
    printf("  --help       - Print this help message\n");
    printf("  -d directory - Create directory\n");
    printf("  -f filename  - Create empty file\n");
    printf("  -f filename -t \"text\"\tCreate file with specified text\n");
}

void create_directory(char *directory) {
    if (mkdir(directory, 0777) == -1) {
        perror("Error creating directory");
    } else {
        printf("Directory created successfully\n");
    }
}

void create_file(char *filename, char *text) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
    } else {
        if (text != NULL) {
            fprintf(file, "%s", text);
            printf("File %s created with text \"%s\"\n", filename, text);
        } else {
            printf("Empty file %s created\n", filename);
        }
        fclose(file);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Error : No arguments is provided\n");
        printf("Use 'cdf --help' to see the list of supported arguments.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0) {
        print_version();
    } else if (strcmp(argv[1], "--help") == 0) {
        print_help();
    } else if (strcmp(argv[1], "-d") == 0) {
        if (argc == 3) {
            create_directory(argv[2]);
        } else {
            for (int i = 2; i < argc; i++) {
                create_directory(argv[i]);
            }
        }
    } else if (strcmp(argv[1], "-f") == 0) {
        if (argc == 3) {
            create_file(argv[2], NULL);
        } else if (argc == 5 && strcmp(argv[3], "-t") == 0) {
            create_file(argv[2], argv[4]);
        } else {
            printf("Error : Invalid arguments\n");
            printf("Use 'cdf --help' to see the list of supported arguments.\n");
            return 1;
        }
    } else {
        printf("Error: Invalid arguments\n");
        printf("Use 'cdf --help' to see the list of supported arguments.\n");
        return 1;
    }

    return 0;
}
