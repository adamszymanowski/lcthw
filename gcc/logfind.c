#include <glob.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dbg.h"

#define ARGUMENT_LENGTH_LIMIT 256

// Documentation
// instead of searching *.log files, it searches *.c files in its current directory
// the idea behind this decision is it doesn't require any additional setup (it's self-contained)
// search capabilities:
// so far it uses only one argument

// linked list for line data 
typedef struct LinePosition {
    size_t start;
    size_t end;
    size_t number;
    int found;
    struct LinePosition *next;
} LinePosition;


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
    int glob_return_value = glob("*.c", 0, NULL, glob_results);
    
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
            debug("%ld files", glob_results->gl_pathc);
        }
    }

    for (int i = 0; i < glob_results->gl_pathc; i++) {
        // wait with the looping for now
    }

    FILE *file_contents = fopen(glob_results->gl_pathv[0], "r");
    check(file_contents, "Could not open file: %s", glob_results->gl_pathv[0]);
    check(fseek(file_contents, 0, SEEK_END) == 0, "SEEK_END on file: %s failed", glob_results->gl_pathv[0])
    const size_t file_size = ftell(file_contents);
    debug("file size is %ld", file_size);
    rewind(file_contents);

    LinePosition *list_head_for_line = malloc(sizeof(LinePosition));
    check(list_head_for_line, "Couldn't allocate memory for line.");
    list_head_for_line->start = 0;
    list_head_for_line->end = 0;
    list_head_for_line->found = 0;
    list_head_for_line->next = NULL;
    LinePosition *list_node_for_line = list_head_for_line;

    for (size_t i = 0, s = 0, start = 0, line_number = 1; i <= file_size; i++) {
        char file_char = fgetc(file_contents);

        if (argv[1][s] == file_char) {
            s++;
        } else {
            s = 0;
        }

        if (s == arg_len) {
            list_node_for_line->found = 1;
            s = 0;
        }        

        if (file_char == '\n' || file_char == EOF) {
            list_node_for_line->start = start;
            list_node_for_line->end = i;
            list_node_for_line->number = line_number++;
            start = (i < file_size ? i+1 : i);
            list_node_for_line->next = malloc(sizeof(LinePosition));
            check(list_node_for_line->next, "Couldn't allocate memory for next line.");
            list_node_for_line->next->found = 0;
            list_node_for_line->next->next = NULL;
            list_node_for_line = list_node_for_line->next;
        }
 
    }

    list_node_for_line = list_head_for_line;
    if (list_node_for_line->end != 0) {
        do {
            if (list_node_for_line->found) {
                printf("%s:%ld:\t", glob_results->gl_pathv[0], list_node_for_line->number);

                check(fseek(file_contents, list_node_for_line->start, 0) == 0, "fseek on file: %s failed", glob_results->gl_pathv[0])

                for (size_t i = 0; i < (list_node_for_line->end-list_node_for_line->start); i++) {
                    char file_char = fgetc(file_contents);
                    printf("%c", file_char);
                }
            }

            list_node_for_line = list_node_for_line->next;

        } while (list_node_for_line->next != NULL);
        printf("\n");
    }

    free(list_head_for_line);
    fclose(file_contents);


    globfree(glob_results);
    free(glob_results);
    return 0;

error:
    globfree(glob_results);
    if (glob_results) free(glob_results);

    return -1;
}