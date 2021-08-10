#include "extern.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//QUEUE

typedef struct Queue { //type queue
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *elements;
} Queue;

//SUCC
int64_t succ(Queue *q, int64_t n) {
    return (n + 1) % q->capacity;
}

//QUEUE CREATE
Queue *queue_create(uint32_t size) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = q->tail = 0;
        q->size = 0;
        q->capacity = size; //decrement
        q->elements = (int64_t *) calloc(size, sizeof(int64_t));
        if (q->elements) {
            return q;
        }
        free(q);
    }
    return (Queue *) 0;
}

//DELETE QUEUE
void queue_delete(Queue **q) {
    if (q) {
        //free(q->elements);
        free(q);
        q = NULL;
    }
}

//EMPTY Q
bool queue_empty(Queue *q) {
    if (q) {
        return q->head == q->tail;
    }
    return true;
}

//FULL Q
bool queue_full(Queue *q) {
    if (q) {
        return succ(q, q->head) == q->tail;
    }
    return true;
}

//QUEUE SIZE
uint32_t queue_size(Queue *q) {
    return q->size;
}

//ENQUEUE
bool enqueue(Queue *q, int64_t j) {
    if (q) {
        if (queue_full(q)) {
            return false;
        }
        q->elements[q->head] = j;
        q->head = succ(q, q->head);
        return true;
    } else {
        return false;
    }
}

//DEQUEUE
bool dequeue(Queue *q, int64_t *j) {
    if (q) {
        if (queue_empty(q)) {
            return false;
        }
        *j = q->elements[q->tail];
        q->tail = succ(q, q->tail);
        return true;
    } else {
        return false;
    }
}

//QUEUE PRINT
void queue_print(Queue *q) {
    for (uint32_t i = 0; i < q->size; i += 1) {
        printf("%ld", q->elements[i]);
    }
}
