# Arkstruct [![UPVD Logo](https://upload.wikimedia.org/wikipedia/fr/e/e6/UPVD_logo.svg)](https://www.univ-perp.fr)

> Generic Data Structures for the C Programming Language

Arkstruct is a header library allowing the use of Generic Data Structures in C.

---

## General

Arkstruct works with extensive uses of C Preprocessor macros.
As such, Data Structures must be **defined once and only once** before being used.

To define a Data Structure, add the specified **prototype** line to a header file and the specified **definition** line to a source file.

The type of Data Structures must contain no illegal characters : `*`, for example, is not usable. To use types with the `*` character, please use a `typedef`.

## Data Structures

### Stack

#### How to use

Header file : `arkstruct/stack.h`

Prototype line : `ARKSTACK_PROTO(type)`

Definition line : `ARKSTACK_DEF(type)`

Available functions :

- arkstack_create(type) - *Returns a pointer to an arkstack*
- arkstack_push(stack, element) - *Pushes an element on top of the stack*
- arkstack_pop(stack) - *Removes and returns the top element of the stack. Undefined behavior if the stack is empty.*
- arkstack_top(stack) - *Returns the top element of the stack*
- arkstack_len(stack) - *Returns the size of the stack*
- arkstack_free(stack) - *Frees the stack*

#### Example

```C
#include <stdio.h>
#include "arkstruct/stack.h"

ARKSTACK_PROTO(int)
ARKSTACK_DEF(int)

int main()
{
    arkstack(int) stack = arkstack_create(int);
    arkstack_push(stack, 5);
    arkstack_push(stack, 42);
    printf("%d %d %d\n",
        arkstack_top(stack),  // 42
        arkstack_pop(stack),  // 42
        arkstack_pop(stack)); // 5
    printf("%d\n", arkstack_len(stack)); // 0
    arkstack_free(stack);
    return 0;
}
```

#### Implementation details

Arkstruct's implementation of the Stack uses a dynamically allocated array of starting size 64, doubling in size every overflow.

---

### Queue

#### How to use

Header file : `arkstruct/queue.h`

Prototype line : `ARKQUEUE_PROTO(type)`

Definition line : `ARKQUEUE_DEF(type)`

Available functions :

- arkqueue_create(type) - *Returns a pointer to an arkqueue*
- arkqueue_enqueue(queue, element) - *Enqueues an element at the end of the queue*
- arkqueue_dequeue(queue) - *Removes and returns the first element of the queue. Undefined behavior if the queue is empty.*
- arkqueue_end(queue) - *Returns the first element of the queue*
- arkqueue_len(queue) - *Returns the size of the queue*
- arkqueue_free(queue) - *Frees the queue*

#### Example

```C
#include <stdio.h>
#include "arkstruct/queue.h"

ARKQUEUE_PROTO(int)
ARKQUEUE_DEF(int)

int main()
{
    arkqueue(int) queue = arkqueue_create(int);
    arkqueue_enqueue(queue, 5);
    arkqueue_enqueue(queue, 42);
    printf("%d %d %d\n",
        arkqueue_end(queue),      // 5
        arkqueue_dequeue(queue),  // 5
        arkqueue_dequeue(queue)); // 42
    printf("%d\n", arkqueue_len(queue)); // 0
    arkqueue_free(queue);
    return 0;
}
```

#### Implementation details

Arkstruct's implementation of the Queue uses a dynamically allocated array of starting size 64, doubling in size every overflow.

When the queue array is half empty, the queue's contents are pushed back to the beginning to the array to save space.

---

## Tests

To test the Data Structures, run the provided Makefile with `make` or `make test`.

## Licensing

Arkstruct is under the MIT Licence, specified in `LICENCE`.

The copyright notice in `LICENCE` must be included in all projects using Arkstruct.
