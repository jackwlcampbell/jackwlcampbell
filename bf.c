//bf.c
#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        // Grimm's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bvf) {
    bv_delete(&(*bvf)->filter); //deleting bit vector of bloom filter
    free(*bvf); //freeing bloom filter and setting it to NULL
    bvf = NULL;
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t index;
    // PRIMARY
    index = hash(bf->primary, oldspeak)
            % bf_size(bf); //getting hash index and setting its corresponding bit
    bv_set_bit(bf->filter, index); //for the primary, secondary, and tertiary arrays.
    // SECONDARY
    index = hash(bf->secondary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, index);
    // TERTIARY
    index = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, index);

    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t index;
    // PRIMARY
    index = hash(bf->primary, oldspeak)
            % bf_size(bf); //getting hash index and getting its corresponding bit
    uint8_t bit1 = bv_get_bit(bf->filter, index); //for the primary, secondary, and tertiary arrays.
    // SECONDARY
    index = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint8_t bit2 = bv_get_bit(bf->filter, index);
    // TERTIARY
    index = hash(bf->tertiary, oldspeak) % bf_size(bf);
    uint8_t bit3 = bv_get_bit(bf->filter, index);
    // CHECK
    if ((bit1 & bit2 & bit3) == 1) { //if all bits are set, return true.
        return true;
    }
    return false; //else return false.
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i += 1) { //iterate throught BF filter and
        if (bv_get_bit(bf->filter, i) == 1) { //count the number of set bits.
            count += 1;
        }
    }
    return count; //return that number.
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
