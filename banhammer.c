//banhammer.c

#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"

#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARGUMENTS "hmst:f:"
#define WORD      "([a-zA-Z0-9]+)(('|-)([a-zA-Z0-9]+))?" //*"

bool h_input = false; //help message
bool m_input = false; //move-to-front
bool s_input = false; //statistics printing
uint32_t t_input = 10000; //hash table size
uint32_t f_input = 1048576; //bloom filter size

FILE *badspeak;
FILE *newspeak;

int optbreak = 0;

//MAIN FUNCTION
int main(int argc, char **argv) {

    //	TAKING IN ARGUMENTS
    char *optptr;
    while ((optbreak = getopt(argc, argv, ARGUMENTS)) != -1) {
        switch (optbreak) {
        case 'h': h_input = true; break; //prints help message
        case 'm': m_input = true; break; //enables move-to-front
        case 's': s_input = true; break; //enables statstics printing
        case 't': t_input = strtoul(optarg, &optptr, 10); break; //ht size
        case 'f': f_input = strtoul(optarg, &optptr, 10); break; //bf size
        default: //if invalid argument is found, help message is printed and program with terminate.
            printf("SYNOPSIS\n");
            printf("  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n\n");
            printf("USAGE\n  ./banhammer [-hsm] [-t size] [-f size]\n\n");
            printf("OPTIONS\n");
            printf("  -h\t\tProgram usage and help.\n");
            printf("  -s\t\tPrint program statistics.\n");
            printf("  -m\t\tEnable move-to-front rule.\n");
            printf("  -t size\tSpecify hash table size (default: 10000).\n");
            printf("  -f size\tSpecify Bloom filter size (default: 2^20).\n");
            return 0;
        }
    }

    //HELP SECTION
    if (h_input == true) {
        printf("SYNOPSIS\n");
        printf("  A word filtering program for the GPRSC.\n");
        printf("  Filters out and reports bad words parsed from stdin.\n\n");
        printf("USAGE\n  ./banhammer [-hsm] [-t size] [-f size]\n\n");
        printf("OPTIONS\n");
        printf("  -h\t\tProgram usage and help.\n");
        printf("  -s\t\tPrint program statistics.\n");
        printf("  -m\t\tEnable move-to-front rule.\n");
        printf("  -t size\tSpecify hash table size (default: 10000).\n");
        printf("  -f size\tSpecify Bloom filter size (default: 2^20).\n");
        return 0;
    }

    //OPENING BADSPEAK
    badspeak = fopen("badspeak.txt", "r");
    if (badspeak == NULL) {
        printf("Error: badspeak.txt == NULL\n");
        return 1;
    }

    //OPENING OLDSPEAK/NEWSPEAK
    newspeak = fopen("newspeak.txt", "r");
    if (newspeak == NULL) {
        printf("Error: newspeak.txt == NULL\n");
        return 1;
    }

    //int terms;
    char bad_word[50];
    char old_word[50];
    char new_word[50];

    BloomFilter *bloom_filter = bf_create(f_input);
    HashTable *hash_table = ht_create(t_input, m_input);

    //READING BADSPEAK
    while (fscanf(badspeak, "%s", bad_word) != EOF) {
        bf_insert(bloom_filter, bad_word); //add to bloom filter
        ht_insert(hash_table, bad_word, NULL); //add to hash table
    }

    //READING OLDSPEAK/NEWSPEAK
    while (fscanf(newspeak, "%s %s", old_word, new_word) != EOF) {
        bf_insert(bloom_filter, old_word); //add oldspeak to bloom filter
        ht_insert(
            hash_table, old_word, new_word); //add both to hash table (str1 = old ; str2 = new)
    }

    //READING FROM STDIN (REGEX)
    LinkedList *rightspeak = ll_create(false); //creating two linked lists to
    LinkedList *thoughtcrime = ll_create(false); //store strings from stdin

    //REGEX IMPLEMENTATION
    regex_t reg_out;
    if (regcomp(&reg_out, WORD, REG_EXTENDED)) { //will compile the regular expression
        fprintf(stderr, "regex fail"); //into an executable
        return 1;
    }

    //POPULATING LINKEDLISTS
    char *word = NULL;

    while ((word = next_word(stdin, &reg_out))
           != NULL) { //while stdin hasn't been completely read out,
        if (bf_probe(bloom_filter, word) == true) { //check the bloom filter to see if there is a
            Node *n = ht_lookup(hash_table, word); //matching string. If not, insert the string to
                //the corresponding linked list.
            if (n != NULL) {
                if (n->newspeak != NULL) { //if there is a key-value, insert into rightspeak.
                    ll_insert(rightspeak, word, n->newspeak);
                }
                if (n->newspeak
                    == NULL) { //if there isn't a key-value pair, insert into thoughtcrime.
                    ll_insert(thoughtcrime, word, NULL);
                }
            }
        }
    }

    if (s_input == false) { //if s_input is false, only print statistics
        //RETURNING MESSAGES TO THE CITIZEN
        if (ll_length(thoughtcrime) > 0
            && ll_length(rightspeak) > 0) { //if there are both bad and good words
            printf("%s", mixspeak_message);
            ll_print(thoughtcrime);
            ll_print(rightspeak);
        }

        if (ll_length(thoughtcrime) == 0
            && ll_length(rightspeak) > 0) { //if there are only bad words
            printf("%s", goodspeak_message);
            ll_print(rightspeak);
        }

        if (ll_length(thoughtcrime) > 0
            && ll_length(rightspeak) == 0) { //if there are only good words
            printf("%s", badspeak_message);
            ll_print(thoughtcrime);
        }
    }

    if (s_input == true) { //if s_input is true, only print statistics.
        //GETTING STATISTICS
        double seeks_double = seeks;
        double links_double = links;
        double ht_count_double = ht_count(hash_table);
        double ht_size_double = ht_size(hash_table); //coverting all integers into
        double bf_count_double = bf_count(bloom_filter); //doubles to have decimal places.
        double bf_size_double = bf_size(bloom_filter);

        double hash_load = 100 * (ht_count_double / ht_size_double);
        double filter_load = 100 * (bf_count_double / bf_size_double);

        //PRINTING STATISTICS
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %f\n", links_double / seeks_double);
        printf("Hash table load: %.6f%%\n", hash_load);
        printf("Bloom filter load: %.6f%%\n", filter_load);
    }

    //CLEARING MEMORY AND CLOSING FILES
    clear_words();
    regfree(&reg_out);

    bf_delete(&bloom_filter); //deleting bloom filter
    ht_delete(&hash_table); //deleting hash table

    ll_delete(&rightspeak); //deleting external linked lists
    ll_delete(&thoughtcrime);

    fclose(badspeak); //closing files
    fclose(newspeak);

    //END
    return 0;
}
