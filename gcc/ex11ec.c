#include <stdio.h>
// Extra Credit
int main()
{
    char name[4] = "Zed";
    printf("name each char: %c %c %c %c\n", name[0], name[1], name[2], name[3]);

    printf("size of name: %lu, size of int: %lu\n", sizeof(name), sizeof(int));

    printf("name as bytes:\n");
    printf("at %p value\t%d\t('%c')\n", name, *name, *name);
    printf("at %p value\t%d\t('%c')\n", name+1, *(name+1), *(name+1));
    printf("at %p value\t%d\t('%c')\n", name+2, *(name+2), *(name+2));
    printf("at %p value\t%d\t('%c')\n", name+3, *(name+3), *(name+3));
    printf("\n");

    printf("reverse-engineering:\n");
    int attempt1 = name[0] << 24 | name[1] << 16 | name[2] << 8 | name[3];
    printf("attempt 1 int value: %d\n", attempt1);
    char *pointer = &attempt1;
    printf("at %p value\t%d\t('%c')\n", pointer, *pointer, *pointer);
    printf("at %p value\t%d\t('%c')\n", pointer+1, *(pointer+1), *(pointer+1));
    printf("at %p value\t%d\t('%c')\n", pointer+2, *(pointer+2), *(pointer+2));
    printf("at %p value\t%d\t('%c')\n", pointer+3, *(pointer+3), *(pointer+3));
    printf("\n");

    int attempt2 = name[3] << 24 | name[2] << 16 | name[1] << 8 | name[0];
    printf("attempt 2 int value: %d\n", attempt2);
    pointer = &attempt2;
    printf("at %p value\t%d\t('%c')\n", pointer, *pointer, *pointer);
    printf("at %p value\t%d\t('%c')\n", pointer+1, *(pointer+1), *(pointer+1));
    printf("at %p value\t%d\t('%c')\n", pointer+2, *(pointer+2), *(pointer+2));
    printf("at %p value\t%d\t('%c')\n", pointer+3, *(pointer+3), *(pointer+3));
    printf("\n");

    return 0;
}