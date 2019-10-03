#include <stdio.h>
#include <string.h>

#include "term_util.h"

#include "stack_test.h"
#include "stacks.h"

#include "queue_test.h"



int main(int argc, char** argv)
{   
    printf("\n");
    int status = 0;
    
    printf("%s%sTesting the stacks\n", CSI, WHITE_COLOR);
    status |= test_stack();

    printf("%s%sTesting the queues\n", CSI, WHITE_COLOR);
    status |= test_queue();
    return status;
}