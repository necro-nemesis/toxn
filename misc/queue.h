/*
 *      @(#)queue.h     8.5 (Berkeley) 8/20/94
 * $FreeBSD: src/sys/sys/queue.h,v 1.58.2.1 2005/01/31 23:26:57 imp Exp $
 */

#ifndef TOXN_QUEUE_H
#define TOXN_QUEUE_H

/*
 * Tail queue declarations.
 */
#define TOXNQ_HEAD(name, type)                                          \
struct name {                                                           \
        struct type *tqh_first; /* first element */                     \
        struct type **tqh_last; /* addr of last next element */         \
}

#define TOXNQ_HEAD_INITIALIZER(head)                                    \
        { NULL, &(head).tqh_first }

#define TOXNQ_ENTRY(type)                                               \
struct {                                                                \
        struct type *tqe_next;  /* next element */                      \
        struct type **tqe_prev; /* address of previous next element */  \
}

#define TOXNQ_EMPTY(head)       ((head)->tqh_first == NULL)

#define TOXNQ_FIRST(head)       ((head)->tqh_first)

#define TOXNQ_LAST(head, headname)                                      \
        (*(((struct headname *)((head)->tqh_last))->tqh_last))

#define TOXNQ_NEXT(elm, field) ((elm)->field.tqe_next)

#define TOXNQ_PREV(elm, headname, field)                                \
        (*(((struct headname *)((elm)->field.tqe_prev))->tqh_last))

#define TOXNQ_FOREACH(var, head, field)                                 \
        for ((var) = TOXNQ_FIRST((head));                               \
            (var);                                                      \
            (var) = TOXNQ_NEXT((var), field))

#define TOXNQ_FOREACH_MUTABLE(var, head, field, nvar)                   \
        for ((var) = TOXNQ_FIRST((head));                               \
             (var) && ((nvar) = TOXNQ_NEXT((var), field), (var));       \
             (var) = (nvar))

#define TOXNQ_INIT(head) do {                                           \
        TOXNQ_FIRST((head)) = NULL;                                     \
        (head)->tqh_last = &TOXNQ_FIRST((head));                        \
} while (0)

#define TOXNQ_INSERT_AFTER(head, listelm, elm, field) do {              \
        if ((TOXNQ_NEXT((elm), field) = TOXNQ_NEXT((listelm), field)) != NULL)\
                TOXNQ_NEXT((elm), field)->field.tqe_prev =              \
                    &TOXNQ_NEXT((elm), field);                          \
        else {                                                          \
                (head)->tqh_last = &TOXNQ_NEXT((elm), field);           \
        }                                                               \
        TOXNQ_NEXT((listelm), field) = (elm);                           \
        (elm)->field.tqe_prev = &TOXNQ_NEXT((listelm), field);          \
} while (0)

#define TOXNQ_INSERT_BEFORE(listelm, elm, field) do {                   \
        (elm)->field.tqe_prev = (listelm)->field.tqe_prev;              \
        TOXNQ_NEXT((elm), field) = (listelm);                           \
        *(listelm)->field.tqe_prev = (elm);                             \
        (listelm)->field.tqe_prev = &TOXNQ_NEXT((elm), field);          \
} while (0)

#define TOXNQ_INSERT_HEAD(head, elm, field) do {                        \
        if ((TOXNQ_NEXT((elm), field) = TOXNQ_FIRST((head))) != NULL)   \
                TOXNQ_FIRST((head))->field.tqe_prev =                   \
                    &TOXNQ_NEXT((elm), field);                          \
        else                                                            \
                (head)->tqh_last = &TOXNQ_NEXT((elm), field);           \
        TOXNQ_FIRST((head)) = (elm);                                    \
        (elm)->field.tqe_prev = &TOXNQ_FIRST((head));                   \
} while (0)

#define TOXNQ_INSERT_TAIL(head, elm, field) do {                        \
        TOXNQ_NEXT((elm), field) = NULL;                                \
        (elm)->field.tqe_prev = (head)->tqh_last;                       \
        *(head)->tqh_last = (elm);                                      \
        (head)->tqh_last = &TOXNQ_NEXT((elm), field);                   \
} while (0)

#define TOXNQ_REMOVE(head, elm, field) do {                             \
        if ((TOXNQ_NEXT((elm), field)) != NULL)                         \
                TOXNQ_NEXT((elm), field)->field.tqe_prev =              \
                    (elm)->field.tqe_prev;                              \
        else {                                                          \
                (head)->tqh_last = (elm)->field.tqe_prev;               \
        }                                                               \
        *(elm)->field.tqe_prev = TOXNQ_NEXT((elm), field);              \
} while (0)

#endif
