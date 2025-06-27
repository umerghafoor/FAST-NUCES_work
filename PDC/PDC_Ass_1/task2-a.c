// Umer Ghafoor
// 22i-2328
// PDC A1
// Task 2
#define _GNU_SOURCE
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
#include <basetsd.h>

#if defined(__linux__)
    #include <sched.h>
#elif defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach/mach.h>
    #include <mach/thread_policy.h>
#endif

#define MAX_FILES 1000000
#define MAX_WORD_LEN 100
#define HASH_TABLE_SIZE 100003

int NO_OF_THREADS = 100;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int64_t total_word_count = 0;
int64_t unique_word_count = 0;
int use_affinity = 0;

typedef struct WordEntry {
    char word[MAX_WORD_LEN];
    int64_t count;
    struct WordEntry *next;
} WordEntry;

WordEntry *hash_table[HASH_TABLE_SIZE];
int64_t file_count = 0;
int64_t file_index = 0;
char files[MAX_FILES][512];

uint64_t get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t result = tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
    return result;
}

///////////////////////////////////////////////////////////////////////////
////                      Function Prototypes                          ////
///////////////////////////////////////////////////////////////////////////

void set_thread_affinity(int thread_id);

///////////////////////////////////////////////////////////////////////////
////                      Utility Functions                            ////
///////////////////////////////////////////////////////////////////////////

unsigned int hash_function(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + tolower(*str);
        str++;
    }
    return hash % HASH_TABLE_SIZE;
}

void insert_or_update_word(const char *word) {
    unsigned int index = hash_function(word);

    pthread_mutex_lock(&mutex);
    WordEntry *entry = hash_table[index];

    while (entry != NULL) {
        if (strcmp(entry->word, word) == 0) {
            entry->count++;
            pthread_mutex_unlock(&mutex);
            return;
        }
        entry = entry->next;
    }

    WordEntry *new_entry = (WordEntry *)malloc(sizeof(WordEntry));
    if (new_entry == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        pthread_mutex_unlock(&mutex);
        return;
    }
    strcpy(new_entry->word, word);
    new_entry->count = 1;
    new_entry->next = hash_table[index];
    hash_table[index] = new_entry;
    unique_word_count++;

    pthread_mutex_unlock(&mutex);
}

void process_text(char *text) {
    char *token = strtok(text, " \t\n\r.,!?;:\"()[]{}<>");

    while (token != NULL) {
        if (strlen(token) > 0) {
            total_word_count++;
            insert_or_update_word(token);
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

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file)) {
        process_text(buffer);
    }
    fclose(file);
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

void print_results(FILE *result_file) {
    fprintf(result_file, "\nTotal Words: %ld\n", total_word_count);
    fprintf(result_file, "Unique Words: %ld\n", unique_word_count);

    fprintf(result_file, "\nTerm Frequencies:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        WordEntry *entry = hash_table[i];
        while (entry != NULL) {
            fprintf(result_file, "%s - %ld times\n", entry->word, entry->count);
            entry = entry->next;
        }
    }
}

void cleanup_hash_table() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        WordEntry *entry = hash_table[i];
        while (entry != NULL) {
            WordEntry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
////                      Thread Functions                             ////
///////////////////////////////////////////////////////////////////////////

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

void set_thread_affinity(int thread_id) {
    if (!use_affinity) return;

    // Reference used for cross-platform affinity setting:
    // https://www.oreilly.com/library/view/c-in-a/059600298X/re09.html

    // Not tested on Windows
    #if defined(__linux__)
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(thread_id % sysconf(_SC_NPROCESSORS_ONLN), &cpuset);
        pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);

    #elif defined(_WIN32)
        DWORD_PTR mask = 0;

        // for (int core_id = 0; core_id < 64; core_id += 2) {
        //     mask |= (1ULL << core_id);
        // }

        mask |= (1ULL << (thread_id % 4));

        SetThreadAffinityMask(GetCurrentThread(), mask); 

    // Not tested on macOS
    #elif defined(__APPLE__)
        thread_affinity_policy_data_t policy = {thread_id % 4};
        thread_policy_set(mach_thread_self(), THREAD_AFFINITY_POLICY, (thread_policy_t)&policy, 1);
    #endif
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: program <directory_path> <No. of Threads> <Affinity 0/1>\n");

        return 1;
        
        // argv[1] = "C:\\Users\\Laptech\\Desktop\\PDC ass1\\test\\2000";
        // argv[1] = "C:\\Users\\Laptech\\Desktop\\PDC ass1\\un\\xml\\en";
        argv[1] = "C:\\Users\\Laptech\\Desktop\\PDC ass1\\test\\2000";
        argv[2] = "1";  // Testing portion of data
        argv[3] = "0";  // Default to no affinity
    }

    NO_OF_THREADS = atoi(argv[2]);
    use_affinity = atoi(argv[3]);

    uint64_t start = get_current_time();

    printf("Scanning directory: %s\n", argv[1]);

    scan_directory(argv[1]);

    printf("Found %ld XML files.\n", file_count);
    if (file_count == 0) {
        printf("No XML files found. Exiting.\n");
        return 1;
    }


    // Prompt user before proceeding
    // char response;
    // printf("Proceed with processing? (y/n): ");
    // scanf(" %c", &response);
    // if (response != 'y' && response != 'Y') {
    //     printf("Exiting.\n");
    //     return 0;
    // }

    uint64_t endScan = get_current_time();
    printf("Time taken to scan directory: %ld microseconds\n", (endScan - start) / 1000);

    printf("Processing files...\n");

    pthread_t threads[NO_OF_THREADS];
    for (int i = 0; i < NO_OF_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }
    for (int i = 0; i < NO_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    uint64_t end = get_current_time();
    printf("Time taken to process files: %ld microseconds\n", (end - endScan) / 1000);

    // Open result file to write output
    FILE *result_file = fopen("result.txt", "w");
    if (!result_file) {
        printf("Error opening result.txt for writing.\n");
        return 1;
    }

    // Print results to the file
    print_results(result_file);

    // Close the file
    fclose(result_file);

    cleanup_hash_table(); // Free allocated memory for the hash table
    return 0;
}
