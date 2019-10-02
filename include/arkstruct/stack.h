#pragma once

#include <stdlib.h>


#define arkstack(type)                                                              \
    ARKSTACK_ ## type*

#define ARKSTACK_PROTO(type)                                                        \
    typedef struct ARKSTACK_ ## type  ARKSTACK_ ## type;                            \
    struct ARKSTACK_ ## type                                                        \
    {                                                                               \
        size_t top;                                                                 \
        size_t size;                                                                \
        type* stack;                                                                \
                                                                                    \
        int (*pushFunc)(struct ARKSTACK_ ## type *stack, type elem);                \
        type (*popFunc)(struct ARKSTACK_ ## type *stack);                           \
        type (*topFunc)(struct ARKSTACK_ ## type *stack);                           \
        size_t (*lenFunc)(struct ARKSTACK_ ## type *stack);                         \
        void (*freeFunc)(struct ARKSTACK_ ## type *stack);                          \
    };                                                                              \
                                                                                    \
    int ARKSTACK_ ## type ## _push(struct ARKSTACK_ ## type *stack, type elem);     \
    type ARKSTACK_ ## type ## _pop(struct ARKSTACK_ ## type *stack);                \
    type ARKSTACK_ ## type ## _top(struct ARKSTACK_##type *stack);                  \
    size_t ARKSTACK_ ## type ## _len(struct ARKSTACK_##type *stack);                \
    void ARKSTACK_ ## type ## _free(struct ARKSTACK_ ## type *stack);               \
    struct ARKSTACK_ ## type * ARKSTACK_ ## type ## _create();                                                                 

#define ARKSTACK_DEF(type)                                                          \
    int ARKSTACK_ ## type ## _push(struct ARKSTACK_ ## type *stack, type elem)      \
    {                                                                               \
        stack->stack[stack->top++] = elem;                                          \
        if(stack->top >= stack->size)                                               \
        {                                                                           \
            size_t newSize = stack->size * 2;                                       \
            type* newStack = realloc(stack->stack, newSize * sizeof(type));         \
            if(newStack == NULL)                                                    \
            {                                                                       \
                free(stack->stack);                                                 \
                stack->stack = NULL;                                                \
                return 0;                                                           \
            }                                                                       \
            stack->stack = newStack;                                                \
            stack->size = newSize;                                                  \
        }                                                                           \
        return 1;                                                                   \
    }                                                                               \
                                                                                    \
    type ARKSTACK_ ## type ## _pop(struct ARKSTACK_ ## type *stack)                 \
    {                                                                               \
        return stack->stack[--stack->top];                                          \
    }                                                                               \
                                                                                    \
    type ARKSTACK_ ## type ## _top(struct ARKSTACK_##type *stack)                   \
    {                                                                               \
        return stack->stack[stack->top-1];                                          \
    }                                                                               \
                                                                                    \
    size_t ARKSTACK_ ## type ## _len(struct ARKSTACK_##type *stack)               \
    {                                                                               \
        return stack->top;                                                          \
    }                                                                               \
                                                                                    \
    void ARKSTACK_ ## type ## _free(struct ARKSTACK_ ## type *stack)                \
    {                                                                               \
        free(stack->stack);                                                         \
        free(stack);                                                                \
    }                                                                               \
                                                                                    \
    struct ARKSTACK_ ## type * ARKSTACK_ ## type ## _create()                       \
    {                                                                               \
        struct ARKSTACK_ ## type *r = calloc(1, sizeof(struct ARKSTACK_ ## type));  \
        if(r == NULL)                                                               \
            return NULL;                                                            \
        r->top = 0; r->size = 64;                                                   \
        r->stack = calloc(64, sizeof(type));                                        \
        r->pushFunc = ARKSTACK_ ## type ## _push;                                   \
        r->popFunc = ARKSTACK_ ## type ## _pop;                                     \
        r->topFunc = ARKSTACK_ ## type ## _top;                                     \
        r->lenFunc = ARKSTACK_ ## type ## _len;                                     \
        r->freeFunc = ARKSTACK_ ## type ## _free;                                   \
        return r;                                                                   \
    }      

#define arkstack_push(astack, elem)                                                \
    astack->pushFunc(astack, elem)

#define arkstack_pop(astack)                                                       \
    astack->popFunc(astack)

#define arkstack_top(astack)                                                       \
    astack->topFunc(astack)

#define arkstack_len(astack)                                                       \
    astack->lenFunc(astack)

#define arkstack_free(astack)                                                      \
    astack->freeFunc(astack)

#define arkstack_create(type)                                                      \
    ARKSTACK_ ## type ## _create()