#include <stdio.h>
// Extra Credit
int main(int argc, char *argv[])
{
    int i = 0;
    const int maximum = 8;
    const int number_of_arguments = argc - 1;

    if (number_of_arguments == 0) {
        printf("You have no arguments. You suck.\n");
    } else if (number_of_arguments >= 2 && number_of_arguments <= maximum) {
        printf("Here's your arguments:\n");

        for (i = 1; i < argc ; i++) {
            printf("%d: %s\n", i,  argv[i]);
        }
    } else {
        printf("You have too many (%d) arguments. Maximum is %d. You suck.\n", number_of_arguments, maximum);
    }
    
    return 0;
}