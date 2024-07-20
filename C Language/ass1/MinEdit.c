#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_CODE_LENGTH 1000

char code[MAX_CODE_LENGTH];
void createNewFile();
void editFile(char *filename);
void saveFile(char *filename, char *code);
void compileFile(char *filename);
void runFile(char *filename);

int main(int argc, char *argv[]) {
    int choice = 1;
    char filename[MAX_FILENAME_LENGTH]; 
    while (choice != 0) {
        printf("Enter your Choice (0 to exit):\n");
        printf("1. Create New File\n");
        printf("2. Edit Existing File\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        switch(choice) {
            case 0:
                printf("Exiting MinEdit.\n");
                break;
            case 1:
                createNewFile();
                break;
            case 2:
                printf("Enter filename: ");
                scanf("%s", filename);
                editFile(filename);            
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }
    return 0;
}

void createNewFile() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter filename: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file.\n");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    editFile(filename);
}


void readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file for reading.\n");
        exit(EXIT_FAILURE);
    }

    size_t pos = 0;
    int c;
    while ((c = fgetc(file)) != EOF && pos < MAX_CODE_LENGTH - 1) {
        code[pos++] = c;
    }
    code[pos] = '\0'; 
    fclose(file);
}

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", code);
    fclose(file);
}

void clearScreen() {
    printf("\033[2J\033[1;1H");
}


void displayCode(int cursorPos) {
    int i;
    for (i = 0; i < strlen(code); i++) {
        if (i == cursorPos) {
            printf("\033[7m"); // Reverse video (highlight)
        }
        putchar(code[i]);
        if (i == cursorPos) {
            printf("\033[0m"); // Reset video attributes
        }
    }
}

void editFile(char *filename) {
    if (!isatty(STDIN_FILENO)) {
        printf("Error: Not a terminal.\n");
        exit(EXIT_FAILURE);
    }

    readFromFile(filename);

    struct termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios new_termios = orig_termios;
    new_termios.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    int pos = 0;
    while (1) {
        clearScreen();
        displayCode(pos);
        printf("\ness arrow keys to navigate, type ':s' to save, ':x' to close,:!c to complie :!e to run or start typing to edit.\n");

        char ch = getchar();
        if (ch == 27) { 
            ch = getchar(); 
            if (ch == '[') {
                ch = getchar(); 
                switch (ch) {
                    case 'A': 
                        if (pos > 0) {
                            pos--;
                        }
                        break;
                    case 'B': 
                        if (pos < strlen(code)) {
                            pos++;
                        }
                        break;
                    default:
                        break;
                }
            }
        } else if (ch == ':') 
        {
            ch = getchar(); 
            if (ch == 's') { 
                tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
                saveToFile(filename);
                break;
            }
            if(ch=='x')
            {
                printf("Are you sure you want to close the file? (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    break;
                }
            }
            if(ch=='!')
            {
                ch = getchar(); 
                        if (ch == 'c') {
                            tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
                            saveToFile(filename);
                            compileFile(filename);
                        } else if (ch == 'e') {
                            tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
                            saveToFile(filename);
                            compileFile(filename);
                            runFile(filename);
                        }
                        break;
            }

        } else if (ch == 127) { 
            if (pos > 0) 
            {
                memmove(&code[pos - 1], &code[pos], strlen(code) - pos + 1);
                pos--;
            }
        } else {
            code[pos++] = ch;
            if (pos >= MAX_CODE_LENGTH - 1) {
                printf("Error: Maximum code length exceeded.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);

}

void saveFile(char *filename, char *code) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", code);
    fclose(file);
}

void compileFile(char *filename) {
    char command[100];
    sprintf(command, "gcc %s -o %s.out", filename, filename);
    int result = system(command);
    if (result == 0) {
        printf("Compilation successful.\n");
    } else {
        printf("Compilation failed.\n");
    }
}

void runFile(char *filename) {
    char command[100];
    sprintf(command, "./%s.out", filename);
    int result = system(command);
    if (result == 0) {
        printf("Execution successful.\n");
    } else {
        printf("Execution failed.\n");
    }
}
