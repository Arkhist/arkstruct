#include "term_util.h"

#include <stdio.h>
#include <string.h>

#include "queues.h"
#include "queue_test.h"

ARKQUEUE_DEF(int);
ARKQUEUE_DEF(str_t);

int test_queue()
{
    printf("\t%s%sTesting int queue... ", CSI, WHITE_COLOR);
    arkqueue(int) queue1 = arkqueue_create(int);
    if(queue1 == NULL)
    {
        CLEAR_LINE();
        printf("\t\t%s%sFailure to init a queue.%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
        return QUEUE_FAIL;
    }
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    printf("\tEnqueuing 150 elements... ");
    for(int i = 0; i < 150; i++)
        arkqueue_enqueue(queue1, i);
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    arkqueue(int) queue2 = arkqueue_create(int);
    printf("\tDequeue and enqueue to another queue... ");
    for(int i = arkqueue_len(queue1); i > 0; i--)
    {
        if(arkqueue_end(queue1) != 150-i)
        {
            CLEAR_LINE();
            printf("\t\t%s%sInconsistent top value of Queue 1%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
            return QUEUE_FAIL;
        }
        arkqueue_enqueue(queue2, arkqueue_dequeue(queue1));
    }
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    printf("\tFreeing queue1... ");
    arkqueue_free(queue1);
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);

    printf("\tChecking queue2 consistency... ");
    for(int i = arkqueue_len(queue2); i > 0; i--)
        if(arkqueue_dequeue(queue2) != 150-i)
        {
            CLEAR_LINE();
            printf("\t\t%s%sQueue 2 inconsistent%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
            return QUEUE_FAIL;
        }
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);
    arkqueue_free(queue2);

    printf("\tChecking char* type queue... ");
    arkqueue(str_t) queue3 = arkqueue_create(str_t);
    arkqueue_enqueue(queue3, "He");
    arkqueue_enqueue(queue3, "llo,");
    arkqueue_enqueue(queue3, " World");
    arkqueue_enqueue(queue3, "!");
    char str[18] = {'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0};
    char str2[18] = {0};
    for(int i = arkqueue_len(queue3); i > 0; i--)
        strcat(str2, arkqueue_dequeue(queue3));
    if(strcmp(str2, str) || arkqueue_len(queue3) != 0)
    {
        CLEAR_LINE();
        printf("\t\t%s%schar* queue inconsistent%s%s\n", CSI, RED_COLOR, CSI, WHITE_COLOR);
        return QUEUE_FAIL;
    }
    arkqueue_free(queue3);
    printf("%s%sOK%s%s\n", CSI, GREEN_COLOR, CSI, WHITE_COLOR);


    return 0;
}