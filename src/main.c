#include <stdio.h>

#include "arkstruct/stack.h"

ARKSTACK_DEF(int);

void print(arkstack(int) stack)
{
    for(long int i = arkstack_len(stack); i > 0; i--)
        printf("%d ", arkstack_pop(stack));
    printf("\n");
}

int main(int argc, char** argv)
{   
    arkstack(int) stack = arkstack_create(int);
    arkstack_push(stack, 3);
    arkstack_push(stack, 1);
    arkstack_push(stack, -100);
    print(stack);
    arkstack_free(stack);

    return 0;
}