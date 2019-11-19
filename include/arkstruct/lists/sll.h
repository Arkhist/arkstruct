#pragma once

#define ARKLIST_SLL_TYPE 1

#define arksllist(type)                                                             \
    ARKSLLIST_ ## type*

#define ARKSLLIST_PROTO(type)                                                       \
    typedef struct ARKSLLIST_ ## type  ARKSLLIST_ ## type;                          \
    struct ARKSLLIST_ ## type                                                       \
    {                                                                               \
        struct ARKLIST_ ## type;                                                    \
                                                                                    \
        struct ARKSLLIST_ ## type * next;                                           \
    };                                                                              \
                                                                                    \

#define ARKSLLIST_DEF(type)                                                         \
    struct ARKSLLIST_ ## type * ARKSLLIST_ ## type ## _create()                     \
    {                                                                               \
        struct ARKSLLIST_ ## type *r = calloc(1, sizeof(struct ARKSLLIST_ ## type));\
        if(r == NULL)                                                               \
            return NULL;                                                            \
        r->next = NULL; r->empty = 1;                                               \
        r->setFunc = ARKLIST_ ## type ## _ set;                                     \
                                                                                    \
        r->appendFunc = ARKSLLIST_ ## type ## _append;                              \
        r->insertFunc = ARKSLLIST_ ## type ## _insert;                              \
                                                                                    \
        r->nextFunc = ARKSLLIST_ ## type ## _next;                                  \
        r->getListFunc = ARKSLLIST_ ## type ## _getList;                            \
        r->getFunc = ARKSLLIST_ ## type ## _get;                                    \
                                                                                    \
        r->linkFunc = ARKSLLIST_ ## type ## _link;                                  \
                                                                                    \
        r->popFunc = ARKSLLIST_ ## type ## _pop;                                    \
        r->deleteFunc = ARKSLLIST_ ## type ## _delete;                              \
                                                                                    \
        r->lenFunc = ARKSLLIST_ ## type ## _len;                                    \
                                                                                    \
        r->freeFunc = ARKSLLIST_ ## type ## _free;                                  \
        return r;                                                                   \
    }                                                                               \
                                                                                    \
    int ARKSLLIST_ ## type ## _append (struct ARKLIST_ ## type *list, type elem) {  \
    int ARKSLLIST_ ## type ## _insert(struct ARKLIST_ ## type *list, int index) {   \
                                                                                    \
    struct ARKLIST_ ## type * (*nextFunc)(struct ARKLIST_ ## type *list);           \
    type (*getFunc)(struct ARKLIST_ ## type *list, int index);                      \
    type (*getListFunc)(struct ARKLIST_ ## type *list, int index);                  \
                                                                                    \
    void (*linkFunc)(struct ARKLIST_ ## type *list1, struct ARKLIST_ ## type *list2);\
                                                                                    \
    type (*popFunc)(struct ARKLIST_ ## type *list);                                 \
    type (*deleteFunc)(struct ARKLIST_ ## type *list, int index);                   \
                                                                                    \
    size_t (*lenFunc)(struct ARKLIST_ ## type *list);                               \
                                                                                    \
    void (*freeFunc)(struct ARKLIST_ ## type *list);                                \

