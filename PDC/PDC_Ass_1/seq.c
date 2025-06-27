#include <dirent.h>  // For reading directory
#include <string.h>
#include <cstdio>

// Function to process a single file
void process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    printf("Processing file: %s\n", filename);
    
    // (Use the existing multithreaded logic to process the file here)

    fclose(file);
}

int main() {
    struct dirent *entry;
    DIR *dir = opendir("multiUN");  // Change this to your dataset folder

    if (!dir) {
        perror("Error opening directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".txt")) {  // Process only text files
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "multiUN/%s", entry->d_name);
            process_file(filepath);
        }
    }

    closedir(dir);
    return 0;
}
