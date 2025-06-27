#ifndef IMAGE_FILE_LIST_H
#define IMAGE_FILE_LIST_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>

int is_image_file(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (!ext) return 0;
    return (strcasecmp(ext, ".png") == 0 ||
            strcasecmp(ext, ".jpg") == 0 ||
            strcasecmp(ext, ".jpeg") == 0);
}

char** list_image_files(const char *folder_path, int *count) {
    DIR *dir = opendir(folder_path);
    if (!dir) {
        perror("Error opening directory");
        return NULL;
    }

    struct dirent *entry;
    char **file_list = NULL;
    *count = 0;

    while ((entry = readdir(dir)) != NULL) {
        struct stat path_stat;
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", folder_path, entry->d_name);
        stat(full_path, &path_stat);

        if (S_ISREG(path_stat.st_mode) && is_image_file(entry->d_name)) {
            file_list = realloc(file_list, (*count + 1) * sizeof(char *));
            if (!file_list) {
                perror("Memory allocation error");
                closedir(dir);
                return NULL;
            }

            file_list[*count] = malloc(strlen(full_path) + 1);
            if (file_list[*count]) {
                strcpy(file_list[*count], full_path);
            }

            (*count)++;
        }
    }

    closedir(dir);
    return file_list;
}

#endif