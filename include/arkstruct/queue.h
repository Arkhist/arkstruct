#pragma once

#include <stdlib.h>


#define ARKQUEUE_DEFAULT_SIZE 64

#define arkqueue(type)                                                              \
    ARKQUEUE_ ## type*

#define ARKQUEUE_PROTO(type)                                                        \
    typedef struct ARKQUEUE_ ## type  ARKQUEUE_ ## type;                            \
    struct ARKQUEUE_ ## type                                                        \
    {                                                                               \
        size_t end;                                                                 \
        size_t begin;                                                               \
        size_t size;                                                                \
        type* queue;                                                                \
                                                                                    \
        int (*enqFunc)(struct ARKQUEUE_ ## type *queue, type elem);                 \
        type (*deqFunc)(struct ARKQUEUE_ ## type *queue);                           \
        type (*startFunc)(struct ARKQUEUE_ ## type *queue);                         \
        size_t (*lenFunc)(struct ARKQUEUE_ ## type *queue);                         \
        void (*freeFunc)(struct ARKQUEUE_ ## type *queue);                          \
    };                                                                              \
                                                                                    \
    int ARKQUEUE_ ## type ## _enqueue(struct ARKQUEUE_ ## type *queue, type elem);  \
    type ARKQUEUE_ ## type ## _dequeue(struct ARKQUEUE_ ## type *queue);            \
    type ARKQUEUE_ ## type ## _start(struct ARKQUEUE_##type *queue);                \
    size_t ARKQUEUE_ ## type ## _len(struct ARKQUEUE_##type *queue);                \
    void ARKQUEUE_ ## type ## _free(struct ARKQUEUE_ ## type *queue);               \
    struct ARKQUEUE_ ## type * ARKQUEUE_ ## type ## _create();

#define ARKQUEUE_DEF(type)                                                          \
    int ARKQUEUE_ ## type ## _enqueue(struct ARKQUEUE_ ## type *queue, type elem)   \
    {                                                                               \
        queue->queue[queue->end++] = elem;                                          \
        if(queue->end >= queue->size)                                               \
        {                                                                           \
            size_t newSize = queue->size * 2;                                       \
            type* newQueue = realloc(queue->queue, newSize * sizeof(type));         \
            if(newQueue == NULL)                                                    \
            {                                                                       \
                free(queue->queue);                                                 \
                queue->queue = NULL;                                                \
                return 0;                                                           \
            }                                                                       \
            queue->queue = newQueue;                                                \
            queue->size = newSize;                                                  \
        }                                                                           \
        return 1;                                                                   \
    }                                                                               \
                                                                                    \
    type ARKQUEUE_ ## type ## _dequeue(struct ARKQUEUE_ ## type *queue)             \
    {                                                                               \
        type r = queue->queue[queue->begin++];                                      \
        if(queue->begin >= queue->size/2)                                           \
        {                                                                           \
            for(int i = queue->begin; i < queue->end; i++)                          \
                queue->queue[i - queue->begin] = queue->queue[i];                   \
            queue->end = queue->end - queue->begin;                                 \
            queue->begin = 0;                                                       \
        }                                                                           \
        return r;                                                                   \
    }                                                                               \
                                                                                    \
    type ARKQUEUE_ ## type ## _start(struct ARKQUEUE_##type *queue)                 \
    {                                                                               \
        return queue->queue[queue->begin];                                          \
    }                                                                               \
                                                                                    \
    size_t ARKQUEUE_ ## type ## _len(struct ARKQUEUE_##type *queue)                 \
    {                                                                               \
        return queue->end - queue->begin;                                           \
    }                                                                               \
                                                                                    \
    void ARKQUEUE_ ## type ## _free(struct ARKQUEUE_ ## type *queue)                \
    {                                                                               \
        free(queue->queue);                                                         \
        free(queue);                                                                \
    }                                                                               \
                                                                                    \
    struct ARKQUEUE_ ## type * ARKQUEUE_ ## type ## _create()                       \
    {                                                                               \
        struct ARKQUEUE_ ## type *r = calloc(1, sizeof(struct ARKQUEUE_ ## type));  \
        if(r == NULL)                                                               \
            return NULL;                                                            \
        r->begin = 0; r->size = ARKQUEUE_DEFAULT_SIZE; r->end = 0;                  \
        r->queue = calloc(ARKQUEUE_DEFAULT_SIZE, sizeof(type));                     \
        r->enqFunc = ARKQUEUE_ ## type ## _enqueue;                                 \
        r->deqFunc = ARKQUEUE_ ## type ## _dequeue;                                 \
        r->startFunc = ARKQUEUE_ ## type ## _start;                                 \
        r->lenFunc = ARKQUEUE_ ## type ## _len;                                     \
        r->freeFunc = ARKQUEUE_ ## type ## _free;                                   \
        return r;                                                                   \
    }

#define arkqueue_enqueue(aqueue, elem)                                              \
    aqueue->enqFunc(aqueue, elem)

#define arkqueue_dequeue(aqueue)                                                    \
    aqueue->deqFunc(aqueue)

#define arkqueue_end(aqueue)                                                        \
    aqueue->startFunc(aqueue)

#define arkqueue_len(aqueue)                                                        \
    aqueue->lenFunc(aqueue)

#define arkqueue_free(aqueue)                                                       \
    aqueue->freeFunc(aqueue)

#define arkqueue_create(type)                                                       \
    ARKQUEUE_ ## type ## _create()