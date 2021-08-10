#include "bubble.h"

#include "extern.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bubble_sort(uint32_t *array, uint32_t len) {
    bool swapped = true;
    while (swapped == true) {
        swapped = false;
        for (uint32_t x = 1; x < len; x += 1) {
            compares += 1;
            if (array[x] < array[x - 1]) {
                SWAP(array, x, x - 1);
                moves += 3;
                swapped = true;
            }
        }
        len -= 1;
    }
}
