#include <stdlib.h>
#include <stdio.h>
// Extra Credit - stack;
struct StackNode {
    char *point_to;
    struct StackNode *prev;
};

struct Stack {
    struct StackNode *top;
};

struct Stack *Stack_create()
{
    struct Stack *stack = malloc(sizeof(struct Stack));
    struct StackNode *top = malloc(sizeof(struct StackNode));
    top->prev = NULL;
    top->point_to = NULL;
    stack->top = top;
    return stack;
}

void Stack_push(struct Stack *stack, char *point_to)
{
    struct StackNode *node = malloc(sizeof(struct StackNode));
    node->point_to = point_to;
    node->prev = stack->top;
    stack->top = node;
}

char *Stack_pop(struct Stack *stack)
{
    if (!stack->top->prev) {
        return NULL;
    }

    char *address = stack->top->point_to;
    struct StackNode *new_top = stack->top->prev;
    free(stack->top);
    stack->top = new_top;

    return address;
}

void Stack_destroy(struct Stack *stack)
{
    while(Stack_pop(stack)) {}
    free(stack->top);
    free(stack);
}

int main(int argc, char *argv[])
{
    struct Stack *stack = Stack_create();

    for (int i = 0; i < argc; i++) {
        Stack_push(stack, argv[i]);
    }

    char *string = Stack_pop(stack);
        
    while(string)
    {
        printf("%s\n", string);
        string = Stack_pop(stack);
    }

    Stack_destroy(stack);

    return 0;
}