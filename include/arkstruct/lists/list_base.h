#pragma once

#define ARKLIST_NO_IMPLEM 0

#define arklist(type)                                                               \
    ARKLIST_ ## type*

#define ARKLIST_PROTO(type)                                                         \
    typedef struct ARKLIST_ ## type  ARKLIST_ ## type;                              \
    struct ARKLIST_ ## type                                                         \
    {                                                                               \
        type data;                                                                  \
        int implem;                                                                 \
        char empty;                                                                 \
                                                                                    \
        void (*setFunc)(struct ARKLIST_ ## type *list, type elem);                  \
                                                                                    \
        int (*appendFunc)(struct ARKLIST_ ## type *list, type elem);                \
        int (*insertFunc)(struct ARKLIST_ ## type *list, type elem, int index);     \
                                                                                    \
        struct ARKLIST_ ## type * (*nextFunc)(struct ARKLIST_ ## type *list);       \
        struct ARKLIST_ ## type * (*getListFunc)(struct ARKLIST_ ## type *list, int index);\
                                                                                    \
        void (*catFunc)(struct ARKLIST_ ## type *list1, struct ARKLIST_ ## type *list2);\
                                                                                    \
        void (*deleteFunc)(struct ARKLIST_ ## type *list, int index);               \
                                                                                    \
        size_t (*lenFunc)(struct ARKLIST_ ## type *list);                           \
                                                                                    \
        void (*freeFunc)(struct ARKLIST_ ## type *list);                            \
    };                                                                              \
                                                                                    \
    type ARKLIST_ ## type ## _data(struct ARKLIST_ ## type *list);                  \
    int ARKLIST_ ## type ## _implem(struct ARKLIST_ ## type *list);                 

#define ARKLIST_DEF(type)                                                           \
    void ARKLIST_ ## type ## _set(struct ARKLIST_ ## type *list, type elem) {       \
        list->data = elem;                                                          \
        list->empty = 0;                                                            \
    }                                                                               

#define arklist_set(alist, elem)                                                    \
    alist->setFunc(alist, elem)

#define arklist_append(alist, elem)                                                 \
    alist->appendFunc(alist, elem)

#define arklist_insert(alist, elem, index)                                          \
    alist->insertFunc(alist, elem, index)

#define arklist_next(alist)                                                         \
    alist->nextFunc(alist)

#define arklist_getList(alist, index)                                               \
    alist->getListFunc(alist, index)

#define arklist_data(alist)                                                         \
    alist->data

#define arklist_empty(alist)                                                        \
    alist->empty

#define arklist_cat(alist1, alist2)                                                 \
    alist1->catFunc(alist1, alist2)

#define arklist_delete(alist, index)                                                \
    alist->deleteFunc(alist, index)

#define arklist_len(alist)                                                          \
    alist->lenFunc(alist)

#define arklist_implem(alist)                                                       \
    alist->implem

#define arklist_free(alist)                                                         \
    alist->freeFunc(alist)

#define arklist_create(type)                                                        \
    ARKLIST_ ## type ## _create()