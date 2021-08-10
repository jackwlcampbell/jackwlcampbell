#include "shell.h"

#include "extern.h"
#include "gaps.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void shell_sort(uint32_t *array, uint32_t len) {
    for (uint32_t x = 0; x < GAPS; x += 1) {
        uint32_t gap = gaps[x];
        if (gap > len) {
            continue;
        }
        for (uint32_t y = gap; y < len; y += 1) {
            uint32_t z = y;
            int64_t temp = array[y];
            moves += 1;
            compares += 1;
            while (z >= gap && temp < array[z - gap]) {
                compares += 1;
                SWAP(array, z, z - gap);
                moves += 3;
                z -= gap;
            }
            array[z] = temp;
            moves += 1;
        }
    }
}
