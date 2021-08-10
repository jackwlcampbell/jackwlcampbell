#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include "helper.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ARGUMENTS "hi:o:"

//encode
//MAIN ENCODING FILE WITH ARUGEMENTS ETC

bool h_input = false;
bool i_input = false;
bool o_input = false;

char *file_in = NULL;
char *file_out = NULL;

FILE *infile;
FILE *outfile;

int optbreak = 0;

//MAIN FUNCTION
int main(int argc, char **argv) {

    while ((optbreak = getopt(argc, argv, ARGUMENTS)) != -1) {
        switch (optbreak) {
        case 'h': h_input = true; break;
        case 'i':
            i_input = true;
            file_in = optarg;
            break;
        case 'o':
            o_input = true;
            file_out = optarg;
            break;
        default:
            printf("SYNOPSIS\n  A Hamming(8, 4) systematic code generator.\n\n");
            printf("USAGE\n  ./encode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h\t\tProgram usage and help.\n");
            printf("  -i infile\tInput data to encode.\n");
            printf("  -o outfile\tOutput of encoded data.\n");
            return 0;
        }
    }

    //HELP SECTION
    if (h_input == true) {
        printf("SYNOPSIS\n  A Hamming(8, 4) systematic code generator.\n\n");
        printf("USAGE\n  ./encode [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        printf("  -h\t\tProgram usage and help.\n");
        printf("  -i infile\tInput data to encode.\n");
        printf("  -o outfile\tOutput of encoded data.\n");
        return 0;
    }

    //OPENING INFILE
    if (i_input == true) {
        infile = fopen(file_in, "r");
        if (infile == NULL) {
            printf("Error: infile == NULL\n");
            return 1;
        }
    }
    if (i_input == false) {
        infile = stdin;
    }

    //OPENING OUTFILE
    if (o_input == true) {
        outfile = fopen(file_out, "w");
        if (outfile == NULL) {
            printf("Error: outfile == NULL\n");
            return 1;
        }
    }
    if (o_input == false) {
        outfile = stdout;
    }

    //CREATING PARITY MATRIX
    BitMatrix *parity_mb = bm_create(4, 8); //works
    //ROW 0
    bm_set_bit(parity_mb, 0, 0);
    bm_set_bit(parity_mb, 0, 5);
    bm_set_bit(parity_mb, 0, 6);
    bm_set_bit(parity_mb, 0, 7);

    //ROW 1
    bm_set_bit(parity_mb, 1, 1);
    bm_set_bit(parity_mb, 1, 4);
    bm_set_bit(parity_mb, 1, 6);
    bm_set_bit(parity_mb, 1, 7);

    //ROW 2
    bm_set_bit(parity_mb, 2, 2);
    bm_set_bit(parity_mb, 2, 4);
    bm_set_bit(parity_mb, 2, 5);
    bm_set_bit(parity_mb, 2, 7);

    //ROW 3
    bm_set_bit(parity_mb, 3, 3);
    bm_set_bit(parity_mb, 3, 4);
    bm_set_bit(parity_mb, 3, 5);
    bm_set_bit(parity_mb, 3, 6);

    //bm_print(parity_mb);

    //GETTING DATA
    char result_char;
    uint8_t result_int;

    while ((result_char = fgetc(infile)) != EOF) {
        result_int = (uint8_t) result_char;
        uint8_t message1 = lower_nibble(result_int);
        uint8_t message2 = upper_nibble(result_int);
        uint8_t code1 = ham_encode(parity_mb, message1);
        uint8_t code2 = ham_encode(parity_mb, message2);
        fputc(code1, outfile);
        fputc(code2, outfile);
    }

    //SETTING FILE PERMISSIONS (FROM ASSIGNMENT DOCUMENT)
    struct stat statbuf;
    fstat(fileno(infile), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    //CLOSING FILES
    if (i_input == true) {
        fclose(infile);
    }

    if (o_input == true) {
        fclose(outfile);
    }

    //ENDING PROGRAM
    return 0;
}
