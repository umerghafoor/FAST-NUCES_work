#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int choice;
    int exit_choice = 0;
    
    while (!exit_choice) {
        printf("CDF Menu:\n");
        printf("1. Select 1 for version\n");
        printf("2. Select 2 for help\n");
        printf("3. Select 3 to create a directory (directories)\n");
        printf("4. Select 4 to create an empty file\n");
        printf("5. Select 5 to create a file with text\n");
        printf("6. Select 6 to exit\n"); 
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                execl("./cdf", "cdf", "--version", NULL);
                break;
            case 2:
                execl("./cdf", "cdf", "--help", NULL);
                break;
            case 3:
                {
                    char directoryName[100];
                    printf("Enter directory name: ");
                    scanf("%s", directoryName);
                    execl("./cdf", "cdf", "-d", directoryName, NULL);
                }
                break;
            case 4:
                {
                    char filename[100];
                    printf("Enter filename: ");
                    scanf("%s", filename);
                    execl("./cdf", "cdf", "-f", filename, NULL);
                }
                break;
            case 5:
                {
                    char filename[100];
                    char text[1000];
                    printf("Enter filename: ");
                    scanf("%s", filename);
                    printf("Enter text: ");
                    getchar(); 
                    fgets(text, sizeof(text), stdin);
                    execl("./cdf", "cdf", "-f", filename, "-t", text, NULL);
                }
                break;
            case 6:
                exit_choice = 1; 
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    
    return 0;
}
