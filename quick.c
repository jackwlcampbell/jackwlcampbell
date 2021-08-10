#include "quick.h"

#include "extern.h"
#include "queue.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint32_t max_stack_size = 0;
uint32_t max_queue_size = 0;

//QUICK SORT - STACK
void quick_sort_stack(uint32_t *array, uint32_t len) {
    int64_t low = 0;
    int64_t high = len - 1;
    Stack *s = stack_create(len);
    stack_push(s, low);
    stack_push(s, high);
    uint32_t size = 2;
    while (stack_empty(s) == false) {
        stack_pop(s, &high);
        stack_pop(s, &low);
        size -= 2;
        int64_t part = partition(array, high, low); //write partition
        if (low < part) {
            stack_push(s, low);
            stack_push(s, part);
            size += 2;
        }
        if (high > part + 1) {
            stack_push(s, part + 1);
            stack_push(s, high);
            size += 2;
        }
        if (size >= max_stack_size) {
            max_stack_size = size;
        }
    }
}

// QUICK SORT - QUEUE
void quick_sort_queue(uint32_t *array, uint32_t len) {
    int64_t low = 0;
    int64_t high = len - 1;
    Queue *q = queue_create(len);
    enqueue(q, low);
    enqueue(q, high);
    uint32_t size = 2;
    while (queue_empty(q) == false) {
        dequeue(q, &low);
        dequeue(q, &high);
        size -= 2;
        int64_t part = partition(array, high, low); //write partition
        if (low < part) {
            enqueue(q, low);
            enqueue(q, part);
            size += 2;
        }
        if (high > part + 1) {
            int64_t newPart = part + 1;
            enqueue(q, newPart);
            enqueue(q, high);
            size += 2;
        }
        if (size >= max_queue_size) {
            max_queue_size = size;
        }
    }
}
