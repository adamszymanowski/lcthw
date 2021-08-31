#include <glob.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dbg.h"

#define ARGUMENT_LENGTH_LIMIT 256

int main(int argc, char *argv[])
{
    check(argc == 2, "Need one argument");
    int length_counter = 0;
    for (int i = 0; argv[1][i] != '\0' && i < ARGUMENT_LENGTH_LIMIT; i++) {
        length_counter++;
    }

    const int arg_len = length_counter;
    debug("%s is %d characters long.", argv[1], arg_len);

    glob_t *glob_results = malloc(sizeof(glob_t));
    check(glob_results, "Could not allocate memory for glob_results");
    int glob_return_value;

    // TODO(Adam):
    // parse command line arguments
    // (DONE) set the length limit and get length
    // * implement or logic
    // * do not allow multiple ors (or whatever)

    // implement line count

    
    glob_return_value = glob("*.c", 0, NULL, glob_results);
    
    switch (glob_return_value) {
        case GLOB_NOSPACE: {
            setinel("glob running out of memory");
        } break;

        case GLOB_ABORTED: {
            setinel("glob read error");
        } break;

        case GLOB_NOMATCH: {
            setinel("glob no matches found");
        } break;

        default: {
            log_info("glob successfull");
        }
    }

    for (int i = 0; i < glob_results->gl_pathc; i++) {
        // wait with the looping for now
    }

    FILE *file_contents = fopen(glob_results->gl_pathv[0], "r");
    check(file_contents, "Could not open file: %s", glob_results->gl_pathv[0]);
    
    int line_count = 1;
    size_t current_file_position = 0;
    size_t current_line_start = 0;

    char file_char = fgetc(file_contents);
    while (file_char != EOF) {
        if (file_char == '\n') {
            printf("%s:%d:\t", glob_results->gl_pathv[0], line_count++);
            
            fseek(file_contents, current_line_start, 0);
            char line_char = fgetc(file_contents);
            
            while (line_char != '\n') {
                printf("%c", line_char);
                line_char = fgetc(file_contents);

            }
            printf("\n");
            current_line_start = current_file_position;
            fseek(file_contents, current_file_position, 0);
        }
        file_char = fgetc(file_contents);
        current_file_position = ftell(file_contents);
    }
    printf("%s:%d:\t", glob_results->gl_pathv[0], line_count++);
    
    fseek(file_contents, current_line_start, 0);
    char line_char = fgetc(file_contents);
    while (line_char != '\n') {

        if (line_char == EOF) { 
            printf("\n");
            break;
        }
        printf("%c", line_char);
        line_char = fgetc(file_contents);

    }
    fclose(file_contents);

    globfree(glob_results);
    free(glob_results);
    return 0;

error:
    globfree(glob_results);
    if (glob_results) free(glob_results);

    return -1;
}