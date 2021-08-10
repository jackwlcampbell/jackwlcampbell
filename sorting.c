#include "bubble.h"
#include "extern.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ARGUMENTS "absqQr:n:p:"

//TAKE IN ARGUEMENTS

int main(int argc, char **argv) {
    Set sort_options = set_empty();
    enum { ALL, BUBBLE, SHELL, QUICK_STACK, QUICK_QUEUE };
    int optbreak = 0;
    char *optptr;
    int r_input = 13371453;
    int n_input = 100;
    int p_input = 100;
    while ((optbreak = getopt(argc, argv, ARGUMENTS)) != -1) {
        switch (optbreak) {
        case 'a': sort_options = set_insert(sort_options, ALL); break;
        case 'b': sort_options = set_insert(sort_options, BUBBLE); break;
        case 's': sort_options = set_insert(sort_options, SHELL); break;
        case 'q': sort_options = set_insert(sort_options, QUICK_STACK); break;
        case 'Q': sort_options = set_insert(sort_options, QUICK_QUEUE); break;
        case 'r': r_input = strtoul(optarg, &optptr, 10); break;
        case 'n': n_input = strtoul(optarg, &optptr, 10); break;
        case 'p': p_input = strtoul(optarg, &optptr, 10); break;
        default:
            printf(
                "Select at least one sort to perform.\nSYNOPSIS\n\tA collection of "
                "comparison-based sorting algorithms.\n\nUSAGE\n\t./sorting [-absqQn:p:r:] [-n "
                "length] [-p elements] [-r seed]\n\nOPTIONS\n-a              Enable all sorts.\n-b "
                "             Enable Bubble Sort.\n-s              Enable Shell Sort.\n-q          "
                "    Enable Quick Sort (Stack).\n-Q              Enable Quick Sort (Queue).\n-n "
                "length       Specify number of array elements.\n-p elements     Specify number of "
                "elements to print.\n-r seed         Specify random seed.\n");
            return -1;
        }
    }

    //MAIN

    if (set_member(sort_options, ALL) || set_member(sort_options, BUBBLE)) {
        moves = 0;
        compares = 0;

        uint32_t array[n_input];
        srand(r_input);
        for (int a = 0; a < n_input; a += 1) {
            array[a] = rand();
        }
        printf("Bubble Sort\n");
        bubble_sort(array, n_input);
        printf("%d elements, %d moves, %d compares\n", n_input, moves, compares);
        for (int i = 0; i < p_input; i += 1) {
            if (n_input >= 1000) {
                break;
            }
            if (i < n_input && i % 5 == 0 && i != 0) {
                printf("\n");
            }
            if (i < n_input) {
                printf("%13" PRIu32, array[i]);
            }
        }
        printf("\n");
    }

    if (set_member(sort_options, ALL) || set_member(sort_options, SHELL)) {
        moves = 0;
        compares = 0;

        uint32_t array[n_input];
        srand(r_input);
        for (int a = 0; a < n_input; a += 1) {
            array[a] = rand();
        }
        printf("Shell Sort\n");
        shell_sort(array, n_input);
        printf("%d elements, %d moves, %d compares\n", n_input, moves, compares);
        for (int i = 0; i < p_input; i += 1) {
            if (n_input >= 1000) {
                break;
            }
            if (i < n_input && i % 5 == 0 && i != 0) {
                printf("\n");
            }
            if (i < n_input) {
                printf("%13" PRIu32, array[i]);
            }
        }
        printf("\n");
    }

    if (set_member(sort_options, ALL) || set_member(sort_options, QUICK_STACK)) {
        moves = 0;
        compares = 0;

        uint32_t array[n_input];
        srand(r_input);
        for (int a = 0; a < n_input; a += 1) {
            array[a] = rand();
        }
        printf("Quick Sort (Stack)\n");
        quick_sort_stack(array, n_input);
        printf("%d elements, %d moves, %d compares\nMax stack size: %d\n", n_input, moves, compares,
            max_stack_size);
        for (int i = 0; i < p_input; i += 1) {
            if (n_input >= 1000) {
                break;
            }
            if (i < n_input && i % 5 == 0 && i != 0) {
                printf("\n");
            }
            if (i < n_input) {
                printf("%13" PRIu32, array[i]);
            }
        }
        printf("\n");
    }

    if (set_member(sort_options, ALL) || set_member(sort_options, QUICK_QUEUE)) {
        moves = 0;
        compares = 0;

        uint32_t array[n_input];
        srand(r_input);
        for (int a = 0; a < n_input; a += 1) {
            array[a] = rand();
        }
        printf("Quick Sort (Queue)\n");
        quick_sort_queue(array, n_input);
        printf("%d elements, %d moves, %d compares\nMax queue size: %d\n", n_input, moves, compares,
            max_queue_size);
        for (int i = 0; i < p_input; i += 1) {
            if (n_input >= 1000) {
                break;
            }
            if (i < n_input && i % 5 == 0 && i != 0) {
                printf("\n");
            }
            if (i < n_input) {
                printf("%13" PRIu32, array[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
