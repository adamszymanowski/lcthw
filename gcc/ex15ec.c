#include <stdio.h>
// Extra Credit
int main(int argc, char *argv[])
{
    char **argv_ptr = argv; // point to address of the first string
    
    for (int i = 0; i < argc; i++) {
        printf("arg[%d]\t\t0x%p\t%s\t%lu\n", i, (argv_ptr+i), *(argv_ptr+i), sizeof(*(argv_ptr+i)));
        printf("------\n");
        char *arg_ch_ptr = *(argv_ptr+i); // point to address of first char of current argument string
        
        int j = 0;
        for (j = 0; *(arg_ch_ptr+j) != '\0'; j++) {
            printf("arg[%d][%d]\t0x%p\t%c\t%lu\n", i, j, (arg_ch_ptr+j), *(arg_ch_ptr+j), sizeof(*(arg_ch_ptr+j)));
        }
        // 'print' null at the end of string too
        printf("arg[%d][%d]\t0x%p\t%c\t%lu\n", i, j, (arg_ch_ptr+j), *(arg_ch_ptr+j), sizeof(*(arg_ch_ptr+j)));
        printf("\n");
    }

    return 0;
}