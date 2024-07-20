#include <stdio.h>
#include <stdlib.h> // for atoi function

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <day> <month>\n", argv[0]);
        return 1;
    }

    int day = atoi(argv[1]);   // Convert the first command line argument to integer
    int month = atoi(argv[2]); // Convert the second command line argument to integer

    switch (month) {
        case 1:  // January
            printf(  (day < 20) ? "Capricorn" : "Aquarius");
            break;
        case 2:  // February
            printf(  (day < 19) ? "Aquarius" : "Pisces");
            break;
        case 3:  // March
            printf(  (day < 21) ? "Pisces" : "Aries");
            break;
        case 4:  // April
            printf(  (day < 20) ? "Aries" : "Taurus");
            break;
        case 5:  // May
            printf(  (day < 21) ? "Taurus" : "Gemini");
            break;
        case 6:  // June
            printf(  (day < 21) ? "Gemini" : "Cancer");
            break;
        case 7:  // July
            printf(  (day < 23) ? "Cancer" : "Leo");
            break;
        case 8:  // August
            printf(  (day < 23) ? "Leo" : "Virgo");
            break;
        case 9:  // September
            printf(  (day < 23) ? "Virgo" : "Libra");
            break;
        case 10: // October
            printf(  (day < 23) ? "Libra" : "Scorpio");
            break;
        case 11: // November
            printf(  (day < 22) ? "Scorpio" : "Sagittarius");
            break;
        case 12: // December
            printf(  (day < 22) ? "Sagittarius" : "Capricorn");
            break;
        default:
            printf("Invalid month.\n");
    }

    return 0;
}
