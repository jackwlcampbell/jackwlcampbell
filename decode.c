//DECODE

#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ARGUMENTS "hi:o:v"

bool h_input = false;
bool i_input = false;
bool o_input = false;
bool v_input = false;

char *file_in = NULL;
char *file_out = NULL;

int infile;
int outfile;

int optbreak = 0;

//MAIN FUNCTION
int main(int argc, char **argv) {

    while ((optbreak = getopt(argc, argv, ARGUMENTS)) != -1) {
        switch (optbreak) {
        case 'h': h_input = true; break;
        case 'v': v_input = true; break; //enables statstics printing
        case 'i':
            i_input = true;
            file_in = optarg;
            break;
        case 'o':
            o_input = true;
            file_out = optarg;
            break;
        default:
            printf("SYNOPSIS\n  A Huffman decoder.\n");
            printf("  Decompresses a file using the Huffman coding algorithm.\n\n");
            printf("USAGE\n  ./decode [-h] [-i infile] [-o outfile]\n\n");
            printf("OPTIONS\n");
            printf("  -h\t\tProgram usage and help.\n");
            printf("  -v\t\tPrint compression statistics.\n");
            printf("  -i infile\tInput file to decompress.\n");
            printf("  -o outfile\tOutput of decompressed data.\n");
            return 0;
        }
    }

    //HELP SECTION
    if (h_input == true) {
        printf("SYNOPSIS\n  A Huffman decoder.\n");
        printf("  Decompresses a file using the Huffman coding algorithm.\n\n");
        printf("USAGE\n  ./decode [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n");
        printf("  -h\t\tProgram usage and help.\n");
        printf("  -v\t\tPrint compression statistics.\n");
        printf("  -i infile\tInput file to decompress.\n");
        printf("  -o outfile\tOutput of decompressed data.\n");
        return 0;
    }

    //OPENING INFILE
    if (i_input == true) {
        infile = open(file_in, O_RDONLY, 0);
        if (infile == -1) {
            printf("ERROR: infile\n");
            return 1;
        }
    }
    if (i_input == false) {
        infile = 0;
    }

    //OPENING OUTFILE
    if (o_input == true) {
        outfile = open(file_out, O_WRONLY | O_CREAT, 0);
        if (outfile == -1) {
            printf("ERROR: outfile\n");
            return 1;
        }
    }
    if (o_input == false) {
        outfile = 1;
    }

    //SETTING PERMISSIONS OF INFILE = OUTFILE.
    struct stat statbuf1;
    fstat(infile, &statbuf1); //populating buffer from infile
    fchmod(outfile, statbuf1.st_mode); //assigning permissions from infile to outfile

    //READ IN HEADER FROM INFILE
    Header header;
    uint32_t bytes_read;

    int header_size = sizeof(Header);
    // HEADER_CONTENTS
    // -magic number
    // -permissions
    // -tree_size
    // -file_size

    bytes_read = read_bytes(infile, (uint8_t *) &header, header_size);
    if (bytes_read > sizeof(Header)) {
        printf("ERROR: bytes_written > sizeof(Header)\n");
        return -1;
    }

    //CHECKING IF MAGIC NUMBER VALUE HAS CHANGED
    if (header.magic != MAGIC) {
        printf("ERROR: magic number changed.\n");
        close(infile);
        close(outfile);
        return -1;
    }

    //READING TREE DUMP
    uint32_t tree_bytes = header.tree_size;
    uint8_t *tree_dump
        = (uint8_t *) calloc(tree_bytes, sizeof(uint8_t)); //allocating tree dump memory.

    read_bytes(infile, (uint8_t *) tree_dump, tree_bytes); //reading the number of bytes of the
        //infile-tree to the newly created tree.

    //REBUILDING TREE
    Node *tree_root = rebuild_tree(tree_bytes, tree_dump);

    //DECODING
    uint64_t symbols_read = 0;
    uint8_t out_bit;
    Node *n;

    while (symbols_read < header.file_size) {
        n = tree_root;
        while (n->left != NULL && n->right != NULL) {
            if (read_bit(infile, &out_bit) == false) {
                printf("ERROR: read_bit() == false\n");
                return -1;
            }

            // if the bit returned is 0, travel down the left path.
            // if the bit returned is 1, travel down the right path.
            (out_bit == 0) ? (n = n->left) : (n = n->right);
        }
        symbols_read += 1;
        write_bytes(outfile, &n->symbol, 1);
    }

    //PRINTING COMPRESSION STATISTICS
    if (v_input == true) {
        struct stat statbuf2;
        fstat(outfile, &statbuf2); //populating buffer from outfile
        fprintf(stderr, "Compressed file size: %ld bytes\n", statbuf1.st_size);
        fprintf(stderr, "Decompressed file size: %ld bytes\n", statbuf2.st_size);
        double numerator = statbuf1.st_size;
        double denominator = statbuf2.st_size;
        fprintf(stderr, "Space saving: %.2f%%\n", 100 * (1 - (numerator / denominator)));
    }

    free(tree_dump);

    //CLOSING FILES
    close(infile);
    close(outfile);

} //EOF
