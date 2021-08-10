#include "queue.h"

#include <inttypes.h>

#ifndef __EXTERN_H__
#define __EXTERN_H__ extern

extern uint32_t moves;
extern uint32_t compares;

//PARTITION
uint32_t partition(uint32_t *array, int64_t high, int64_t low);

//SWAP
void SWAP(uint32_t *array, int64_t x, int64_t y);

#endif
