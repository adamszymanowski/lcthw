#include <stdio.h>
// Extra Credit
int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("You need to pass at least one argument.\n");
        return 1;
    }

    const char difference_between_cases = 'a' - 'A'; 

    for (int i = 1; i < argc; i++) {
        for (int j = 0, letter = argv[i][0]; letter != '\0'; j++, letter = argv[i][j]) { // use comma (,) to initialize letter in for-loop 
            if (letter >= 'a' && letter <= 'z') { // remove all extraenous uppercase letters 
                printf("%c", letter - difference_between_cases); // Use math to convert lowercase to uppercase
            }
        }
        printf(" ");
    }
    printf("\n");
}