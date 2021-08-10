#include "graph.h"
#include "share.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Path { //TAKEN FROM ASSIGNMENT DOCUMENT
    Stack *vertices;
    uint32_t length;
} Path;

//PATH CREATE
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

//PATH PUSH VERTEX
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (stack_full(p->vertices) == true) { //returns false if stack is full
        return false;
    }
    if (stack_empty(p->vertices) == true) { //pushes vertice to stack if its empty
        stack_push(p->vertices, v);
        return true;
    }
    uint32_t x;
    stack_peek(p->vertices, &x);
    p->length = p->length + graph_edge_weight(G, x, v);
    stack_push(p->vertices, v);
    return true;
}

//PATH POP VERTEX
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices) == true) { //returns false if there is nothing to pop
        return false;
    }
    uint32_t x;
    stack_pop(p->vertices, v);
    stack_peek(p->vertices, &x);
    p->length = p->length - graph_edge_weight(G, x, *v);
    return true;
}

//PATH VERTICE
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

//PATH LENGTH
uint32_t path_length(Path *p) {
    return p->length;
}

//PATH COPY
void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

//PATH PRINT
void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
