#pragma once

#define arklist(type)                                                               \
    ARKLIST_ ## type*

#define ARKLIST_PROTO(type)                                                         \
    typedef struct ARKLIST_ ## type  ARKLIST_ ## type;                              \
    struct ARKLIST_ ## type                                                         \
    {                                                                               \
        type data;                                                                  \
        int implem;                                                                 \
                                                                                    \
        int (*appendFunc)(struct ARKLIST_ ## type *list, type elem);                \
        int (*insertFunc)(struct ARKLIST_ ## type *list, int index);                \
                                                                                    \
        struct ARKLIST_ ## type * (*nextFunc)(struct ARKLIST_ ## type *list);       \
        type (*getFunc)(struct ARKLIST_ ## type, int index);                        \
        type (*dataFunc)(struct ARKLIST_ ## type);                                  \
                                                                                    \
        type (*popFunc)(struct ARKLIST_ ## type *list);                             \
        type (*deleteFunc)(struct ARKLIST_ ## type *list, int index);               \
                                                                                    \
        size_t (*lenFunc)(struct ARKLIST_ ## type *list);                           \
        int (*implemFunc)(struct ARKLIST_ ## type *list);                           \
                                                                                    \
        void (*freeFunc)(struct ARKLIST_ ## type *list);                            \
    };                                                                              \
                                                                                    \
    type ARKLIST_ ## type ## _data(struct ARKLIST_ ## type *list);                  \
    int ARKLIST_ ## type ## _implem(struct ARKLIST_ ## type *list);

#define ARKLIST_DEF(type)                                                           \
    type ARKLIST_ ## type ## _data(struct ARKLIST_ ## type *list)                   \
    {                                                                               \
        return list->data;                                                          \
    }                                                                               \
                                                                                    \
    int ARKLIST_ ## type ## _implem(struct ARKLIST_ ## type *list)                  \
    {                                                                               \
        return list->implem;                                                        \
    }

#define arklist_append(alist, elem)                                                 \
    alist->appendFunc(alist, elem)

#define arklist_insert(alist, elem, index)                                          \
    alist->insertFunc(alist, elem, index)

#define arklist_next(alist)                                                         \
    alist->nextFunc(alist)

#define arklist_get(astack, index)                                                  \
    alist->getFunc(astack, index)

#define arklist_data(alist)                                                         \
    alist->dataFunc(alist)

#define arklist_pop(alist)                                                          \
    alist->popFunc(alist)

#define arklist_delete(alist, index)                                                \
    alist->deleteFunc(alist, index)

#define arklist_len(alist)                                                          \
    alist->lenFunc(alist)

#define arklist_implem(alist)                                                       \
    alist->implemFunc(alist)

#define arklist_free(alist)                                                         \
    alist->freeFunc(alist)