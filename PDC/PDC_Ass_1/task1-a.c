// Umer Ghafoor
// 22i-2328
// PDC A1
// Task 1
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

#if defined(__linux__)
    #include <sched.h>
#elif defined(_WIN32)
    #include <windows.h>
#elif defined(__APPLE__)
    #include <mach/mach.h>
    #include <mach/thread_policy.h>
#endif

#define MAX_FILES 100000
// #define MAX_FILES 500 // Using 500 files for testing purpuse
#define MAX_WORD_LEN 100

int NO_OF_THREADS = 100;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int64_t total_word_count = 0, vowel_word_count = 0;
int use_affinity = 0;

typedef struct {
    char word[MAX_WORD_LEN];
    int64_t count;
} WordEntry;

WordEntry word_freq[MAX_FILES * 10];
int64_t word_freq_size = 0;
char files[MAX_FILES][512];
int64_t file_count = 0;
int64_t file_index = 0;

//////////////////////////////////////////////////////////////////////////////
////                      Function Prototypes                             ////
//////////////////////////////////////////////////////////////////////////////

void set_thread_affinity(int thread_id);
int compare_words(const void *a, const void *b);

//////////////////////////////////////////////////////////////////////////////
////                      Utility Functions                               ////
//////////////////////////////////////////////////////////////////////////////

uint64_t get_current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
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

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file)) {
        process_text(buffer);
    }
    fclose(file);
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


//////////////////////////////////////////////////////////////////////////////
////                      Thread Functions                                ////
//////////////////////////////////////////////////////////////////////////////

void *thread_func(void *arg) {
    int thread_id = *(int *)arg;
    free(arg);

    set_thread_affinity(thread_id);  // Set CPU affinity

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

        //// for Even Cores
        // for (int core_id = 0; core_id < 64; core_id += 2) {
        //     mask |= (1ULL << core_id);
        // }
        // mask |= (1ULL << 0);
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
        printf("Usage: %s <directory_path> <No. of Threads> <Affinity: 0/1>\n", argv[0]);
        // return 1;

        // Default values for testing
        argv[1] = "C:\\Users\\Laptech\\Desktop\\PDC ass1\\un\\xml\\en\\2000";
        // argv[1] = "C:\\Users\\Laptech\\Desktop\\PDC ass1\\test\\2000";
        argv[2] = "100";  // Number of threads
        argv[3] = "1";  // Enable affinity
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

    uint64_t endScan = get_current_time();
    printf("Time taken to scan directory: %ld seconds\n", (endScan - start) / 1000000);

    pthread_t threads[NO_OF_THREADS];
    for (int i = 0; i < NO_OF_THREADS; i++) {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&threads[i], NULL, thread_func, thread_id);
    }
    for (int i = 0; i < NO_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    uint64_t end = get_current_time();
    printf("Time taken to process files: %ld seconds\n", (end - endScan) / 1000000);

    print_results();
    return 0;
}

