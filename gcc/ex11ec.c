#include <stdio.h>
#include <stdint.h>
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
    char *pointer = (char *)&attempt1;
    printf("at %p value\t%d\t('%c')\n", pointer, *pointer, *pointer);
    printf("at %p value\t%d\t('%c')\n", pointer+1, *(pointer+1), *(pointer+1));
    printf("at %p value\t%d\t('%c')\n", pointer+2, *(pointer+2), *(pointer+2));
    printf("at %p value\t%d\t('%c')\n", pointer+3, *(pointer+3), *(pointer+3));
    printf("\n");

    int attempt2 = name[3] << 24 | name[2] << 16 | name[1] << 8 | name[0];
    printf("attempt 2 int value: %d\n", attempt2);
    pointer = (char *)&attempt2;
    printf("at %p value\t%d\t('%c')\n", pointer, *pointer, *pointer);
    printf("at %p value\t%d\t('%c')\n", pointer+1, *(pointer+1), *(pointer+1));
    printf("at %p value\t%d\t('%c')\n", pointer+2, *(pointer+2), *(pointer+2));
    printf("at %p value\t%d\t('%c')\n", pointer+3, *(pointer+3), *(pointer+3));
    printf("\n");

    // antoher extra stuff using code from:
    // https://en.wikipedia.org/wiki/Endianness#Optimization
    printf("Extra example:\n");
    uint64_t value = 0x4A;
    union {
        uint8_t u8; uint16_t u16; uint32_t u32; uint64_t u64;
    } u = { .u64 = value };

    printf("0x%lx (%lu) as:\n", value, value);
    printf(" 8-bit unsigned integer: %d\n", u.u8);
    printf("16-bit unsigned integer: %d\n", u.u16);
    printf("32-bit unsigned integer: %d\n", u.u32);
    printf("64-bit unsigned integer: %lu\n", u.u64);
    puts(u.u8 == u.u16 && u.u8 == u.u32 && u.u8 == u.u64 ? "true" : "false");

    printf("\nNow using attempt2 as value:\n");

    value = attempt2;
    u.u32 = value;

    printf("0x%lx (%lu) as:\n", value, value);
    printf(" 8-bit unsigned integer: %d\n", u.u8);
    printf("16-bit unsigned integer: %d\n", u.u16);
    printf("32-bit unsigned integer: %d\n", u.u32);
    printf("64-bit unsigned integer: %lu\n", u.u64);
    puts(u.u8 == u.u16 && u.u8 == u.u32 && u.u8 == u.u64 ? "true" : "false");

    return 0;
}