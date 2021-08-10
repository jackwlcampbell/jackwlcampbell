//CODE

#include "code.h"

#include "defines.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//CODE INIT
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint8_t i = 0; i < MAX_CODE_SIZE; i += 1) {
        c.bits[i] = 0;
    }
    return c;
}

//CODE SIZE
uint32_t code_size(Code *c) {
    return c->top;
}

//CODE EMPTY
bool code_empty(Code *c) { //takes in pointer
    return c->top == 0;
}

//CODE FULL
bool code_full(Code *c) { //takes in pointer
    return c->top == ALPHABET;
}

//CODE PUSH
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c) == true) {
        return false;
    }

    //FINDING BYTE AND INDEX OF BIT
    uint8_t index = c->top % 8;
    uint8_t byte = c->top / 8;
    uint8_t set_bit = 0x1;
    set_bit = set_bit << index;

    //SETTING BIT
    if (bit == 0) {
        c->bits[byte] = c->bits[byte] & ~(set_bit);
    }
    if (bit == 1) {
        c->bits[byte] = c->bits[byte] | set_bit;
    }

    //INCREMENTING TOP
    //printf("%d\n", c->bits[byte]);
    c->top += 1;
    return true;
}

//CODE POP
bool code_pop_bit(Code *c, uint8_t *bit) { //takes in pointer and element
    if (code_empty(c) == true) {
        return false;
    }

    //FINDING BYTE AND INDEX OF BIT
    uint8_t index = c->top % 8;
    uint8_t byte = c->top / 8;

    //GETTING BIT
    *bit = *bit << index;
    *bit = *bit & c->bits[byte];
    *bit = *bit >> index;

    //DECREMENTING TOP
    c->top -= 1;
    return true;
}

void code_print(Code *c) {

    printf("code size: %i bits: ", c->top);

    uint8_t bytes = c->top / 8;
    uint8_t index = c->top % 8;
    uint8_t bits_to_print;

    for (int i = 0; i <= bytes; i += 1) {
        uint8_t byte = c->bits[i];
        (i == bytes) ? (bits_to_print = index) : (bits_to_print = 8);
        for (int j = 0; j < bits_to_print; j += 1) {
            printf("%i ", byte & 0x1);
            byte = byte >> 1;
        }
    }
    printf("\n");
    return;
}
