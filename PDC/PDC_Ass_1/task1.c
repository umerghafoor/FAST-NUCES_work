#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>


// #define NO_OF_THREADS 100
#define MAX_FILES 100000
#define MAX_WORD_LEN 100


int NO_OF_THREADS = 100;
// int MAX_FILES = 100000;
// int MAX_WORD_LEN = 100;


// Varaibles used for processing
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int64_t total_word_count = 0, vowel_word_count = 0;

typedef struct {
    char word[MAX_WORD_LEN];
    int64_t count;
} WordEntry;

WordEntry word_freq[MAX_FILES * 10];
int64_t word_freq_size = 0;

// File list for later reading by threads and processing
char files[MAX_FILES][512];
int64_t file_count = 0;
int64_t file_index = 0;

uint64_t get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t result = tv.tv_sec*(uint64_t)1000000 + tv.tv_usec;
    return result;
} 

int is_vowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void process_text(char *text) {
    char *token = strtok(text, " \t\n\r.,!?;:\"()[]{}<>");

    while (token != NULL) {
        if (strlen(token) > 0) {
            pthread_mutex_lock(&mutex);
            total_word_count++;
            if (is_vowel(token[0])) vowel_word_count++;

            int found = 0;
            for (int64_t i = 0; i < word_freq_size; i++) {
                if (strcmp(word_freq[i].word, token) == 0) {
                    word_freq[i].count++;
                    found = 1;
                    break;
                }
            }
            if (!found && word_freq_size < MAX_FILES * 10) {
                strcpy(word_freq[word_freq_size].word, token);
                word_freq[word_freq_size].count = 1;
                word_freq_size++;
            }
            pthread_mutex_unlock(&mutex);
        }
        token = strtok(NULL, " \t\n\r.,!?;:\"()[]{}<>");
    }
}

void process_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // TODO: Remove this block
    // printf("Processing file: %s\n", filename);
    // printf(".");

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file)) {
        process_text(buffer);
    }
    fclose(file);
}

void *thread_func(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (file_index >= file_count) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        char file_to_process[512];
        strcpy(file_to_process, files[file_index++]);
        pthread_mutex_unlock(&mutex);

        process_file(file_to_process);
    }
    return NULL;
}

void scan_directory(const char *dir_path) {
    struct dirent *entry;
    struct stat path_stat;
    DIR *dir = opendir(dir_path);
    if (!dir) {
        perror("Unable to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
        stat(full_path, &path_stat);

        if (S_ISDIR(path_stat.st_mode)) {
            scan_directory(full_path);
        } else if (strstr(entry->d_name, ".xml")) {
            if (file_count < MAX_FILES) {
                strcpy(files[file_count], full_path);
                file_count++;
            }
        }
    }
    closedir(dir);
}

int compare_words(const void *a, const void *b) {
    return ((WordEntry *)b)->count - ((WordEntry *)a)->count;
}

void print_results() {
    printf("\nTotal Words: %ld\n", total_word_count);
    printf("Words Starting with Vowels: %ld\n", vowel_word_count);

    qsort(word_freq, word_freq_size, sizeof(WordEntry), compare_words);
    printf("\nTop 10 Most Frequent Words:\n");
    for (int64_t i = 0; i < 10 && i < word_freq_size; i++) {
        printf("%s - %ld times\n", word_freq[i].word, word_freq[i].count);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: program <directory_path> <No. of Threads>\n");
        // return 1;
        
        // TODO: Remove this block
        /////////// 
        // manully set the directory path
        // path is C:\\Users\\Laptech\\Desktop\\PDC ass1\\un\\xml\\en
        // this the path of atual data
        argv[1] = "/mnt/1C00FF7F00FF5DE8/Users/Code/PDC ass1/test/dt";
        argv[2] = "100";  // this is very portion of data for testing
        // this is very portion of data for testing
        ///////////
    }

    NO_OF_THREADS = atoi(argv[2]);

    uint64_t start;
    start = get_current_time();

    printf("Scanning directory: %s\n", argv[1]);

    scan_directory(argv[1]);

    printf("Found %ld XML files.\n", file_count); 
    if (file_count == 0) {
        printf("No XML files found. Exiting.\n");
        return 1;
    }

    uint64_t endScan = get_current_time();
    printf("Time taken to scan directory: %ld seconds\n", (endScan - start)/1000000);  // changed to %ld

    // Prompt user before proceeding
    char response;
    printf("Proceed with processing? (y/n): ");
    scanf(" %c", &response);
    if (response != 'y' && response != 'Y') {
        printf("Exiting.\n");
        return 0;
    }

    printf("Processing files...\n");

    pthread_t threads[NO_OF_THREADS];
    for (int i = 0; i < NO_OF_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }
    for (int i = 0; i < NO_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    uint64_t end = get_current_time();
    printf("Time taken to process files: %ld seconds\n", (end - endScan)/1000000);  // changed to %ld

    print_results();
    return 0;
}
