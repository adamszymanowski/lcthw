#include <stdio.h>

int main(void) // NOTE(Adam): unlike in book, it's void here to avoid complier errors
{
    int areas[] = { 10, 12, 13,14, 20 };
    char name[] = "Zed";
    char full_name[] = {
        'Z', 'e', 'd', 
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w'
    };

    // WARNING: On some systems you may have to change the
    // %ld in this code to a %u since it will usse unsigned ints
    printf("The size of an int: %zd\n", sizeof(int)); // NOTE(Adam): Actually it's %zd on Windows
    printf("The size of areas: %zd\n", sizeof(areas));
    printf("The number of ints in areas: %zd\n", 
            sizeof(areas) / sizeof(int));
    printf("first area is %d, the 2nd: %d\n", areas[0], areas[1]);

    printf("The size of char: %zd\n", sizeof(char));
    printf("The size of name: %zd\n", sizeof(name));
    printf("The number of chars: %zd\n", sizeof(name) / sizeof(char));

    printf("The size of full_name (char[]): %zd\n", sizeof(full_name));
    printf("The number of chars: %zd\n",
            sizeof(full_name) / sizeof(char));
    
    printf("name=\"%s\" and full name=\"%s\"\n", name, full_name);

    return 0;
}