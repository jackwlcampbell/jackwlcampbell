#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//STACK
typedef struct Stack { //TAKEN FROM ASSIGNMENT DOCUMENT
    uint32_t top;
    uint32_t capacity;
    uint32_t *elements;
} Stack;

//STACK CREATE
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->elements = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->elements) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//STACK DELETE
void stack_delete(Stack **s) { //takes in address of pointer
    if (*s && (*s)->elements) {
        free((*s)->elements);
        free(*s);
        *s = NULL;
    }
    return;
}

//STACK SIZE
uint32_t stack_size(Stack *s) {
    return s->top;
}

//STACK EMPTY
bool stack_empty(Stack *s) { //takes in pointer
    return s->top == 0;
}

//STACK FULL
bool stack_full(Stack *s) { //takes in pointer
    return s->top == s->capacity;
}

//STACK PUSH
bool stack_push(Stack *s, uint32_t i) {
    if (stack_full(s)) {
        s->capacity *= 2;
        s->elements = (uint32_t *) realloc(s->elements, s->capacity * sizeof(uint32_t));
    }
    s->elements[s->top] = i;
    s->top += 1;
    return true;
}

//STACK POP
bool stack_pop(Stack *s, uint32_t *i) { //takes in pointer and element
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *i = s->elements[s->top];
    return true;
}

//STACK PEEK
bool stack_peek(Stack *s, uint32_t *i) {
    if (stack_empty(s) == true) {
        return false;
    }
    *i = s->elements[s->top - 1];
    return true;
}

//STACK COPY
void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top;
    dst->capacity = src->capacity;
    for (uint32_t i = 0; i < src->capacity; i += 1) {
        dst->elements[i] = src->elements[i];
    }
}

//STACK PRINT
void stack_print(Stack *s, FILE *outfile, char *cities[]) { //TAKEN FROM ASSIGNMENT DOCUMENT
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->elements[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
