#include "graph.h"

#include "share.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph { //TAKEN FROM ASSIGNMENT DOCUMENT
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
} Graph;

//GRAPH CREATE
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = malloc(sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    for (uint32_t l = 0; l < VERTICES; l += 1) {
        G->visited[l] = false;
    }
    for (uint32_t i = 0; i < VERTICES; i += 1) {
        for (uint32_t j = 0; j < VERTICES; j += 1) {
            G->matrix[i][j] = 0;
        }
    }
    return G;
}

//GRAPH ADD EDGE
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < VERTICES && j < VERTICES) { //INCORRECT
        if (G->undirected == false) {
            G->matrix[i][j] = k;
        }
        if (G->undirected == true) {
            G->matrix[i][j] = k;
            G->matrix[j][i] = k;
        }
    } else {
        printf("Error: edge not within bounds.\n");
        return false;
    }
    return true;
}

//GRAPH HAS EDGE?
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (G->matrix[i][j] != 0) {
        return true;
    }

    if (G->matrix[i][j] == 0) {
        return false;
    }
    return false;
}

//GRAPH EDGE WEIGHT
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    return G->matrix[i][j];
}

//GRAPH VISITED?
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v] == true;
}

//GRAPH UNVISITED?
bool graph_unvisited(Graph *G, uint32_t v) {
    return !(G->visited[v] == true);
}

//GRAPH MARK VISITED
void graph_mark_visited(Graph *G, uint32_t v) {
    G->visited[v] = true;
}

//GRAPH MARK UNVISITED
void graph_mark_unvisited(Graph *G, uint32_t v) {
    G->visited[v] = false;
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i += 1) {
        for (uint32_t j = 0; j < G->vertices; j += 1) {
            printf("%d ", G->matrix[i][j]);
        }
        printf("\n");
    }
}
