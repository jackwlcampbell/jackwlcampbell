//bv.c
#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct BitVector { //(FROM ASSIGNMENT DOCUMENT)
    uint32_t length;
    uint8_t *vector;
};

//BITVECTOR CREATE
BitVector *bv_create(uint32_t length) { //LENGTH: NUMBER OF uint8_t IN ARRAY
    BitVector *bv = (BitVector *) calloc(length, sizeof(BitVector));
    bv->vector = (uint8_t *) calloc((length / 8) + 1, sizeof(uint8_t)); //CREATING AN ARRAY OF BYTES
    bv->length = length;
    return bv;
}

//ERROR: NOT A STRUCTURE OR A UNION ??
void bv_delete(BitVector **v) {
    free((*v)->vector); //free array memory
    free(*v); //free bitvector structure and set it to NULL
    v = NULL;
}

//BITVECTOR LENGTH
uint32_t bv_length(BitVector *v) {
    return v->length;
}

//BITVECTOR SET BIT
void bv_set_bit(BitVector *v, uint32_t i) { //works
    uint8_t v2 = 0x1;
    uint32_t byte = i / 8; //get byte number of index
    uint8_t index = i % 8; //get index within that byte
    v2 = (v2 << index); //shift left control bit by 'index' amount
    v->vector[byte] = (v->vector[byte] | v2); //compute a logical "OR" operator with
} //the control bit and the array at "byte" index.

//BITVECTOR CLEAR BIT
void bv_clr_bit(BitVector *v, uint32_t i) { //works
    uint8_t v2 = 0x1;
    uint32_t byte = i / 8; //get byte number of index
    uint8_t index = i % 8; //get index within that byte
    v2 = (v2 << index); //shift left control bit by 'index' amount
    v->vector[byte] = (v->vector[byte] & ~(v2)); //compute a logical "AND" operator with
} //the inverse control bit and the array at "byte" index.

//BITVECTOR GET BIT
uint8_t bv_get_bit(BitVector *v, uint32_t i) { //works
    uint8_t v2 = 0x1;
    uint32_t byte = i / 8; //get byte number of index
    uint8_t index = i % 8; //get index within that byte
    v2 = (v2 << index); //shift left control bit by 'index' amount
    v2 = (v->vector[byte]
          & v2); //compute a logical "AND" operator with the control bit and the array at "byte" index.
    v2 = (v2 >> index); //shift right control bit by 'index' amount
    return v2;
}

//BITVECTOR PRINT
void bv_print(BitVector *v) {
    for (uint32_t i = 0; i < (v->length); i += 1) {
        printf("%d-", v->vector[i]);
    }
    printf("\n");
}
