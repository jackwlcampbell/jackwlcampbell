//node.c
#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *new_strdup(char *string) {
    if (string == NULL) {
        return NULL;
    }
    char *string_copy
        = (char *) malloc((strlen(string) + 1) * sizeof(char)); //allocate memory for the strcpy()
    strcpy(string_copy, string);
    return string_copy; //return the copied string.
}

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->oldspeak = new_strdup(oldspeak);
    n->newspeak = new_strdup(newspeak);
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak); //frees oldspeak memory
        free((*n)->newspeak); //frees newspeak memory
        free(*n); //frees structure and sets it to NULL
        *n = NULL;
    }
}

void node_print(Node *n) {
    if (n->newspeak != NULL && n->oldspeak != NULL)
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    else if (n->oldspeak != NULL)
        printf("%s\n", n->oldspeak);
}
