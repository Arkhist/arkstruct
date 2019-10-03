#include "term_util.h"

#include <stdio.h>
#include <string.h>

#include "stacks.h"
#include "stack_test.h"

ARKSTACK_DEF(int);
ARKSTACK_DEF(str_t);

int test_stack()
{
    printf("%s%sTesting int stack... ", CSI, WHITE_COLOR);
    arkstack(int) stack1 = arkstack_create(int);
    if(stack1 == NULL)
    {
        CLEAR_LINE();
        printf("\t%s%sFailure to init a stack.%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
        return STACK_FAIL;
    }
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    printf("Pushing 150 elements... ");
    for(int i = 0; i < 150; i++)
        arkstack_push(stack1, i);
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    arkstack(int) stack2 = arkstack_create(int);
    printf("Pop and push to another stack... ");
    for(int i = arkstack_len(stack1); i > 0; i--)
    {
        if(arkstack_top(stack1) != i-1)
        {
            CLEAR_LINE();
            printf("\t%s%sInconsistent top value of Stack 1%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
            return STACK_FAIL;
        }
        arkstack_push(stack2, arkstack_pop(stack1));
    }
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    printf("Freeing stack1... ");
    arkstack_free(stack1);
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    printf("Checking stack2 consistency... ");
    for(int i = arkstack_len(stack2); i > 0; i--)
        if(arkstack_pop(stack2) != 150-i)
        {
            CLEAR_LINE();
            printf("\t%s%sStack 2 inconsistent%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
            return STACK_FAIL;
        }
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);
    arkstack_free(stack2);

    printf("Checking char* type stack... ");
    arkstack(str_t) stack3 = arkstack_create(str_t);
    arkstack_push(stack3, "!");
    arkstack_push(stack3, " World");
    arkstack_push(stack3, "llo,");
    arkstack_push(stack3, "He");
    char str[18] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0};
    char str2[18] = {0};
    for(int i = arkstack_len(stack3); i > 0; i--)
        strcat(str2, arkstack_pop(stack3));
    if(strcmp(str2, str))
    {
        CLEAR_LINE();
        printf("\t%s%schar* stack inconsistent%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
        return STACK_FAIL;
    }
    arkstack_free(stack3);
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);


    return 0;
}