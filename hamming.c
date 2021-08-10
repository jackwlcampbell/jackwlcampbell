#include "hamming.h"

#include "bm.h"
#include "bv.h"
#include "helper.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//hamming.c

//CREATE LOOKUP TABLE
uint8_t lookup[] = { 7, 11, 13, 14, 8, 4, 2, 1 };

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {

    //GETTING DATA FROM MESSAGE
    uint32_t msg_length = 4;
    BitMatrix *data_bm = bm_from_data(msg, msg_length);

    //MATRIX MULTIPLICATION
    BitMatrix *output_bm = bm_multiply(data_bm, G);

    //GETTING DATA FROM MULTIPLICATION OUTPUT
    uint8_t code = bm_to_data(output_bm);
    return code;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    uint32_t code_length = 8;

    //GETTING DATA FROM CODE
    BitMatrix *data_bm = bm_from_data(code, code_length);
    printf("data_bm :\n");
    bm_print(data_bm);

    //MATRIX MULTIPLICATION/ERROR SYNDROME
    BitMatrix *error_bm = bm_multiply(data_bm, Ht);
    printf("error_syn :\n");
    bm_print(error_bm);
    uint8_t error_syndrome = bm_to_data(error_bm);

    //GETTING DATA AND PARITY BITS FROM CODE
    uint8_t data_bits = lower_nibble(code);
    uint8_t parity_bits = upper_nibble(code);
    printf("lower msg: %d\n", data_bits);
    printf("upper msg: %d\n", parity_bits);

    //LOOK-UP CHECK
    if (error_syndrome == 0) {
        *msg = data_bits;
        return HAM_OK;
    }
    for (uint32_t i = 0; i < 7; i += 1) {
        if (error_syndrome == lookup[i]) {
            corrected_errors += 1;
            return HAM_CORRECT;
        }
    }
    uncorrected_errors += 1;
    return HAM_ERR;
}
