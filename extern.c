#include "queue.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int64_t element_type; //type element_type

uint32_t moves = 0;
uint32_t compares = 0;

//SWAP
void SWAP(uint32_t *array, int64_t x, int64_t y) {
    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}

///PARTITION
int64_t partition(uint32_t *array, int64_t high, int64_t low) {
    int64_t math = ((high - low) / 2);
    int64_t pivot = array[low + math];
    int64_t x = low - 1;
    int64_t y = high + 1;
    while (x < y) {
        compares += 1;
        x += 1;
        while (array[x] < pivot) {
            compares += 1;
            x += 1;
        }

        y -= 1;
        while (array[y] > pivot) {
            compares += 1;
            y -= 1;
        }

        if (x < y) {
            compares += 1;
            SWAP(array, x, y);
            moves += 3;
        }
    }
    return y;
}
