#include <glob.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dbg.h"

#define ARGUMENT_LENGTH_LIMIT 256

typedef struct LinePos {
    size_t start;
    size_t end;
    unsigned int found;
    struct LinePos *next;
} LinePos;


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
    check(fseek(file_contents, 0, SEEK_END) == 0, "SEEK_END on file: %s failed", glob_results->gl_pathv[0])
    const size_t file_size = ftell(file_contents);
    debug("file size is %ld", file_size);
    rewind(file_contents);

    LinePos *line = malloc(sizeof(LinePos));
    check(line, "Couldn't allocate memory for line.");
    line->start = 0;
    line->end = 0;
    line->found = 0;
    line->next = NULL;
    LinePos *line_linked_list_node = line;

    for (size_t i = 0, s = 0, start = 0; i <= file_size; i++) {
        char file_char = fgetc(file_contents);

        if (argv[1][s] == file_char) {
            s++;
        } else {
            s = 0;
        }

        if (s == arg_len) {
            line_linked_list_node->found = 1;
            s = 0;
        }        

        if (file_char == '\n' || file_char == EOF) {
            line_linked_list_node->start = start;
            line_linked_list_node->end = i;
            start = (i < file_size ? i+1 : i);
            line_linked_list_node->next = malloc(sizeof(LinePos));
            check(line, "Couldn't allocate memory for line.");
            line_linked_list_node->next->found = 0;
            line_linked_list_node->next->next = NULL;
            line_linked_list_node = line_linked_list_node->next;
        }
 
    }

    line_linked_list_node = line;
    if (line_linked_list_node->end != 0) {
        do {
            printf("s:%ld, e:%ld, f:%d\n", line_linked_list_node->start, line_linked_list_node->end, line_linked_list_node->found);
            line_linked_list_node = line_linked_list_node->next;
            //printf("%s:%ld:\t", glob_results->gl_pathv[0], line_count++);

        } while (line_linked_list_node->next != NULL);
    }


    free(line);
    fclose(file_contents);


    globfree(glob_results);
    free(glob_results);
    return 0;

error:
    globfree(glob_results);
    if (glob_results) free(glob_results);

    return -1;
}