//ht.c
#include "ht.h"

#include "bf.h"
#include "ll.h"
#include "node.h"
#include "speck.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable)); //allocates memory for structure
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *)); //allocates memory for array
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    LinkedList *dl = NULL;
    for (uint32_t i = 0; i < (*ht)->size; i += 1) { //frees each element of array
        dl = (*ht)->lists[i];
        if (dl != NULL) {
            ll_delete(&dl);
        }
    }
    free((*ht)->lists); //frees array
    free(*ht); //frees structure and sets it to NULL
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index
        = hash(ht->salt, oldspeak) % ht_size(ht); //gets hash index and returns its ll_lookup
    if (!ht->lists[index]) {
        return NULL;
    }
    return ll_lookup(ht->lists[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht); //gets hash index
    if (!ht->lists[index]) {
        ht->lists[index]
            = ll_create(ht->mtf); //if its not already in the ht, a new ll will be created
    }
    ll_insert(ht->lists[index], oldspeak, newspeak); //then the element will be added to the ll.
    return;
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->lists[i] != NULL) {
            count += 1;
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    printf("HASH TABLE size:%u mtf:%d count:%u\n", ht->size, ht->mtf, ht_count(ht));
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->lists[i] != NULL) {
            printf("Index: %u\n", i);
            ll_print(ht->lists[i]);
        }
    }
    return;
}
