#include "graph.h"
#include "path.h"
#include "share.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARGUMENTS "hvui:o:"

//DFS FUNCTION PROTOTYPE TAKEN FROM ASSIGNMENT DOCUMENT.
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile);

//INITALIZING VARIABLES
bool h_input = false;
bool v_input = false;
bool u_input = false;
bool i_input = false;
bool o_input = false;

char *file_in = NULL;
char *file_out = NULL;

FILE *infile;
FILE *outfile;

int optbreak = 0;

uint32_t x;
uint32_t y;
uint32_t z;
int c;

uint32_t recursive_calls = 0;
uint32_t vertice_count = 0;

//MAIN FUNCTION
int main(int argc, char **argv) {

    while ((optbreak = getopt(argc, argv, ARGUMENTS)) != -1) {
        switch (optbreak) {
        case 'h': h_input = true; break;
        case 'v': v_input = true; break;
        case 'u': u_input = true; break;
        case 'i':
            i_input = true;
            file_in = optarg;
            break;
        case 'o':
            o_input = true;
            file_out = optarg;
            break;
        default:
            printf("SYNOPSIS\n  Traveling Salesman Problem using DFS.\n\n");
            printf("USAGE\n  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -u\t\tUse undirected graph.\n");
            printf("  -v\t\tEnable verbose printing.\n");
            printf("  -h\t\tProgram usage and help.\n");
            printf("  -i infile\tInput containing graph (default: stdin)\n");
            printf("  -o outfile\tOutput of computed path (default: stdout)\n");
            return 1;
        }
    }

    //HELP SECTION
    if (h_input == true) {
        printf("SYNOPSIS\n  Traveling Salesman Problem using DFS.\n\n");
        printf("USAGE\n  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        printf("  -u\t\tUse undirected graph.\n");
        printf("  -v\t\tEnable verbose printing.\n");
        printf("  -h\t\tProgram usage and help.\n");
        printf("  -i infile\tInput containing graph (default: stdin)\n");
        printf("  -o outfile\tOutput of computed path (default: stdout)\n");
        return 0;
    }

    //OPENING INFILE
    if (i_input == true) {
        infile = fopen(file_in, "r");
        if (infile == NULL) {
            printf("Error: infile == NULL\n");
            return 1;
        }
    }
    if (i_input == false) {
        infile = stdin;
    }

    //OPENING OUTFILE
    if (o_input == true) {
        outfile = fopen(file_out, "w");
        if (outfile == NULL) {
            printf("Error: outfile == NULL\n");
            return 1;
        }
    }
    if (o_input == false) {
        outfile = stdout;
    }

    //GETTING NUMBER OF VERTICES
    c = fscanf(infile, "%d\n", &x);
    if (c != 1) {
        printf("Error: c != 1");
        return 1;
    }
    vertice_count = x;
    if (vertice_count <= 1) {
        printf("There is nowhere to go.\n");
        return 1;
    }
    if (vertice_count > VERTICES) {
        printf("Error: vertice_count > VERTICES\n");
        return 1;
    }

    //GETTING CITY NAMES
    char *cities[vertice_count];
    char buffer[4096];

    for (uint32_t i = 0; i < vertice_count; i += 1) {
        fgets(buffer, 4096, infile);
        cities[i] = strdup(buffer);
        cities[i][strlen(cities[i]) - 1] = '\0'; // <-- METHOD TAKEN FROM EUGENES SECTION
    }

    //CREATE GRAPH AND ADD EDGES
    Graph *G = graph_create(vertice_count, u_input);
    while ((c = fscanf(infile, "%d %d %d\n", &x, &y, &z)) != EOF) {
        if (c != 3) {
            printf("Error: malformed edge.\n");
            return 1;
        }
        graph_add_edge(G, x, y, z);
    }

    //CREATING CURRENT AND SHORTEST PATHS
    Path *curr = path_create();
    Path *shortest = path_create();

    uint32_t v = START_VERTEX; // STARTING/ORIGIN VERTEX

    //DEPTH FIRST SEARCH CALL
    dfs(G, v, curr, shortest, cities, outfile);

    //PRINTING PATH RESULTS
    fprintf(outfile, "Path Length: %d\nPath: ", path_length(shortest));
    path_print(shortest, outfile, cities);
    fprintf(outfile, "Total recusive calls: %d\n", recursive_calls);

    //FREEING MEMORY
    //stack_delete(curr->vertices);
    //stack_delete(shortest->vertices);

    //PROGRAM END
    return 0;
}

//DSF FUNCTION 1 ----------------------------------------------------------------------------------------
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {

    //PUSHING VERTICE ONTO PATH
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);

    //HAMILTONIAN PATH CHECK
    if (v == START_VERTEX && path_vertices(curr) == (vertice_count + 1)) {
        if (v_input == true) {
            fprintf(outfile, "Path Length: %d\nPath: ", path_length(curr));
            path_print(curr, outfile, cities);
        }
        if (path_length(curr) < path_length(shortest) || path_length(shortest) == 0) {
            path_copy(shortest, curr);
        }
    }

    //VERTICE POTENTIAL EDGE CHECK / RECURSION CALL
    for (uint32_t i = 0; i < vertice_count; i += 1) {
        if (graph_has_edge(G, v, i) == true) {
            if (graph_visited(G, i) == false
                || ((path_vertices(curr) == (vertice_count)) && i == START_VERTEX)) {
                recursive_calls += 1;
                dfs(G, i, curr, shortest, cities, outfile);
            }
        }
    }

    //POPS VERTICE FROM PATH
    if (path_length(curr) != 0) {
        path_pop_vertex(curr, &v, G);
    }
    if (v != START_VERTEX) {
        graph_mark_unvisited(G, v);
    }
    return;
}
