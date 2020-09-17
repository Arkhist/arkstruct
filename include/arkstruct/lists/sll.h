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
        r->next = NULL;                                                             \
                                                                                    \
        r->appendFunc = ARKSLLIST_ ## type ## _append;                              \
        r->insertFunc = ARKSLLIST_ ## type ## _insert;                              \
                                                                                    \
        r->nextFunc = ARKSLLIST_ ## type ## _next;                                  \
        r->getListFunc = ARKSLLIST_ ## type ## _getList;                            \
                                                                                    \
        r->catFunc = ARKSLLIST_ ## type ## _link;                                   \
                                                                                    \
        r->deleteFunc = ARKSLLIST_ ## type ## _delete;                              \
                                                                                    \
        r->lenFunc = ARKSLLIST_ ## type ## _len;                                    \
                                                                                    \
        r->freeFunc = ARKSLLIST_ ## type ## _free;                                  \
        return r;                                                                   \
    }                                                                               \
                                                                                    \
                                                                                    \
                                                                                    \
    int ARKSLLIST_ ## type ## _append (struct ARKLIST_ ## type *list, type elem) {  \
        if (list->empty) {                                                          \
            list->setFunc(list, elem);                                              \
            return 0;                                                               \
        }                                                                           \
        struct ARKSLLIST_ ## type * next = ARKSLLIST_ ## type ## _create();         \
        if (next == NULL) {                                                         \
            return 1;                                                               \
        }                                                                           \
        list->next = next;                                                          \
        next->setFunc(next, elem);                                                  \
        return 0;                                                                   \
    }                                                                               \
                                                                                    \
    int ARKSLLIST_ ## type ## _insert (struct ARKLIST_ ## type *list, type elem, int index) {  \
        struct ARKLIST_ ## type * pastList = list;                                  \
        for(int i = 0; i < index; i++) {                                            \
            pastList = list;                                                        \
            if(list == NULL)                                                        \
                return 1;                                                           \
            list = list->nextFunc(list);                                            \
        }                                                                           \
        if(list == NULL) {                                                          \
            pastList->appendFunc(pastList, elem);                                   \
            return 0;                                                               \
        }                                                                           \
        struct ARKSLLIST_ ## type * next = ARKSLLIST_ ## type ## _create();         \
        pastList = list->nextFunc(list);                                            \
        if (next == NULL) {                                                         \
            return 1;                                                               \
        }                                                                           \
        ((struct ARKSLLIST_ ## type *)list)->next = next;                           \
        ((struct ARKSLLIST_ ## type *)next)->next = pastList;                       \
        next->setFunc(next, elem);                                                  \
        return 0;                                                                   \
    }                                                                               \
                                                                                    \
    struct ARKSLLIST_ ## type * ARKSLLIST_ ## type ## _nextFunc(struct ARKLIST_ ## type *list) {\
        return ((struct ARKSLLIST_ ## type *)list)->next;                           \
    }                                                                               \
                                                                                    \
    type ARKSLLIST_ ## type ## _getListFunc(struct ARKLIST_ ## type *list, int index) {\
        for(int i = 0; i < index; i++) {                                            \
            if(list == NULL)                                                        \
                return NULL;                                                        \
            list = list->nextFunc(list);                                            \
        }                                                                           \
        return list;                                                                \
    }                                                                               \
                                                                                    \
    void ARKSLLIST_ ## type ## _catFunc(struct ARKLIST_ ## type *list1, struct ARKLIST_ ## type *list2){\
        struct ARKLIST_ ## type *past = list1;                                      \
        while(list1 != NULL) {                                                      \
            past = list1;                                                           \
            list1 = list1->nextFunc(list1);                                         \
        }                                                                           \
        ((struct ARKSLLIST_ ## type *)list1)->next = list2;                         \
    }                                                                               \
                                                                                    \
    void ARKSLLIST_ ## type ## _deleteFunc(struct ARKLIST_ ## type *list, int index) {\
        struct ARKLIST_ ## type * prevList = list;                                  \
        for(int i = 0; i < index; i++) {                                            \
            prevList = list;                                                        \
            list = list->nextFunc(list);                                            \
            if (list == NULL)                                                       \
                return;                                                             \
        }                                                                           \
        ((struct ARKSLLIST_ ## type *)prevList)->next = list->nextFunc(list);       \
    }                                                                               \
                                                                                    \
    size_t ARKSLLIST_ ## type ## _lenFunc(struct ARKLIST_ ## type *list) {          \
        size_t r = 0;                                                               \
        while(list != NULL) {                                                       \
            r++;                                                                    \
            list = list->nextFunc(list);                                            \
        }                                                                           \
                                                                                    \
    void ARKSLLIST_ ## type ## _freeFunc(struct ARKLIST_ ## type *list){            \
        free(list);                                                                 \
    }                                                                               \

#define arksllist_create(type)                                                      \
    ARKSLLIST_ ## type ## _create()