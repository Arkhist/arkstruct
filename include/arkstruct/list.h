#pragma once

#if __STDC_VERSION__ <= 201112L
    #error "Lists are only supported for C11 and more. Please use --std=c11"
#else
    #include "lists/list_base.h"
    #include "lists/sll.h"

#endif