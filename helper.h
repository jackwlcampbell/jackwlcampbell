//helper.h

#ifndef __HELPER_H__
#define __HELPER_H__

#include <stdint.h>

//LOWER NIBBLE
uint8_t lower_nibble(uint8_t val);

//UPPER NIBBLE
uint8_t upper_nibble(uint8_t val);

//PACK BYTE
uint8_t pack_byte(uint8_t upper, uint8_t lower);

//CREATING EXTERNAL VARIABLES FOR DECODE.C
extern uint32_t total_bytes_covered;
extern uint32_t uncorrected_errors;
extern uint32_t corrected_errors;

#endif
