//ll.c
#include "ll.h"

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t seeks = 0; // Number of seeks performed.
uint64_t links = 0; // Number of links traversed.

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->length = 0;
        ll->mtf = mtf;
        ll->head = node_create("head", NULL); //start and end node
        ll->tail = node_create("tail", NULL);
        ll->head->next = ll->tail; // HEAD -> TAIL
        ll->tail->prev = ll->head; // HEAD <- TAIL
    }
    return ll;
}

void ll_delete(LinkedList **ll) {
    Node *n = (*ll)->head;
    Node *nd = NULL;

    while (n != NULL) {
        nd = n;
        n = n->next;
        node_delete(&nd);
    }
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {

    Node *position = ll->head->next;
    seeks += 1;
    //FINDING OLDSPEAK

    while (position != ll->tail && strcmp(position->oldspeak, oldspeak) != 0) {
        links += 1;
        position = position->next; //while string isn't matching, increment links and position.
    }

    if (position == ll->tail) { //if string is never found, return NULL.
        return NULL;
    }

    //MTF LOGIC
    if (ll->head->next != position && ll->mtf == true) { //if node isn't already at the front
        //removing node from ll                          //and mtf is true, perform this logic.
        position->next->prev = position->prev;
        position->prev->next = position->next;

        //adding node to head of ll
        position->prev = ll->head;
        position->next = ll->head->next; //linked list insertion logic
        ll->head->next->prev = position;
        ll->head->next = position;
    }
    return position;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *insert_node
            = node_create(oldspeak, newspeak); //if node isn't already in the ll, insert it.

        //adding to head of ll
        insert_node->prev = ll->head;
        insert_node->next = ll->head->next; //linked list insertion logic
        ll->head->next->prev = insert_node;
        ll->head->next = insert_node;

        //incrementing length
        ll->length += 1;
    }
    return;
}

void ll_print(LinkedList *ll) {
    for (Node *position = ll->head->next; position != ll->tail; position = position->next) {
        node_print(position);
    }
    return;
}
