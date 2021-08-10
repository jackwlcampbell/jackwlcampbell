//bm.c
#include "bm.h"

#include "bv.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct BitMatrix { //(FROM ASSIGNMENT DOCUMENT)
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

//BITMATRIX CREATE
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    uint32_t total_bits = rows * cols;
    BitMatrix *bm
        = (BitMatrix *) calloc(total_bits, sizeof(BitMatrix)); //MIGHT REPLACE total_bits with 1.
    bm->rows = rows;
    bm->cols = cols;
    bm->vector = bv_create(total_bits);
    return bm;
}

//BITMATRIX DELETE
void bm_delete(BitMatrix **m) {
    //bv_delete(m->vector);
    free(m);
    m = NULL;
}

//BITMATRIX ROW NUMBER
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

//BITMATRIX CREATECOLUMNS NUMBER
uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

//BITMATRIX SET BIT
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t input = (r * m->cols + c);
    bv_set_bit(m->vector, input);
}

//BITMATRIX CLEAR BIT
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t input = (r * m->cols + c);
    bv_clr_bit(m->vector, input);
}

//BITMATRIX GET BIT
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint32_t input = (r * m->cols + c);
    return bv_get_bit(m->vector, input);
}

//BITMATRIX FROM DATA
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) { //CHECK IMPLEMENTATION
    uint32_t rows = 1;
    BitMatrix *Data = bm_create(rows, length); // 1 row, (length) columns
    for (uint32_t i = 0; i < length; i += 1) {
        //GET BIT
        uint8_t set_bit = 0x1;
        uint8_t byte_num = i / 8;
        uint8_t index = i % 8;
        for (uint8_t i = byte_num; i > 0; i -= 1) {
            index += 8;
        }
        set_bit = (set_bit << index);
        set_bit = (set_bit & byte);
        set_bit = (set_bit >> index);
        if (set_bit == 0x1) {
            bm_set_bit(Data, 0, i);
        }
        if (set_bit == 0x0) {
            bm_clr_bit(Data, 0, i);
        }
    }
    return Data;
}

//BITMATRIX TO DATA
uint8_t bm_to_data(BitMatrix *m) { //CHECK IMPLEMENTATION
    uint8_t output = 0;
    uint8_t bit;
    BitVector *matrix_vector = m->vector;

    for (uint32_t i = 0; i < 8; i += 1) {
        bit = bv_get_bit(matrix_vector, i);
        if (bit == 0x1) {
            uint8_t result = 1;
            for (uint32_t j = 0; j < i; j += 1) {
                result = (result * 2);
            }
            output = output + result;
        }
    }
    return output;
}

//BITMATRIX MULTIPLICATION (I WROTE THIS ON MY OWN ALTHOUGH IT IS SIMILAR TO THE CLASS SLIDES)
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *C = bm_create(A->rows, B->cols);
    if (B->rows != A->cols) {
        printf("ERROR: columns != rows.");
        return C;
    }
    for (uint32_t i = 0; i < (A->rows); i += 1) {
        for (uint32_t j = 0; j < (B->cols); j += 1) {
            uint8_t element = 0x0;
            for (uint32_t k = 0; k < (A->cols); k += 1) {
                element = element ^ (bm_get_bit(A, i, k) & bm_get_bit(B, k, j));
            }
            if (element == 0x1) {
                bm_set_bit(C, i, j);
            }
        }
    }
    return C;
}

//BITMATRIX PRINT
void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < (m->rows * m->cols); i += 1) {
        if (i % m->cols == 0) {
            printf("\n");
        }
        printf("%d ", bv_get_bit(m->vector, i));
    }
    printf("\n");
}
