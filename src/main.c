#include <stdio.h>
#include <string.h>

#include "term_util.h"

#include "stack_test.h"
#include "stacks.h"



int main(int argc, char** argv)
{   
    printf("\n");
    int status = 0;
    status |= test_stack();
    return status;
}