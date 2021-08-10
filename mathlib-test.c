#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//MAIN FILE

#define ARGUEMENTS "asctl"

int main(int argc, char **argv) {
    int optbreak = 0;
    bool s_input = false;
    bool c_input = false;
    bool t_input = false;
    bool l_input = false;
    while ((optbreak = getopt(argc, argv, ARGUEMENTS))
           != -1) { //breaks once all arguments have been iterated over
        switch (optbreak) {
        case 'a':
            s_input = true;
            c_input = true;
            t_input = true;
            l_input = true;
            break;
        case 's': s_input = true; break;
        case 'c': c_input = true; break;
        case 't': t_input = true; break;
        case 'l': l_input = true; break;
        default:
            fprintf(stderr, "Program usage: ./mathlib-test -[asctl]\n");
            fprintf(stderr, "  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
            fprintf(stderr, "  -s   Runs arcsin tests\n");
            fprintf(stderr, "  -c   Runs arccos tests\n");
            fprintf(stderr, "  -t   Runs arctan tests\n");
            fprintf(stderr, "  -l   Runs log tests\n");
            return -1;
        }
    }

    if (s_input == true) {
        printf("  x            arcSin           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double x = -1; x < 0.0;
             x += 0.1) { //calls functions from -1.0 to 1.0 incrementing by 0.1
            double A1 = arcSin(x);
            double A2 = asin(x);
            double A3 = A1 - A2;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, A1, A2,
                A3); //prints input, student function, library function, and difference.
        }
        for (double y = 0.1; y < 1.0; y += 0.1) {
            double A1 = arcSin(y);
            double A2 = asin(y);
            double A3 = A1 - A2;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", y, A1, A2, A3);
        }
    }

    if (c_input == true) {
        printf("  x            arcCos           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double n = -1; n < 0.0;
             n += 0.1) { //calls functions from -1.0 to 1.0 incrementing by 0.1
            double B1 = arcCos(n);
            double B2 = acos(n);
            double B3 = B1 - B2;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", n, B1, B2,
                B3); //prints input, student function, library function, and difference.
        }
        for (double m = 0.1; m < 1.0; m += 0.1) {
            double B1 = arcCos(m);
            double B2 = acos(m);
            double B3 = B1 - B2;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", m, B1, B2,
                B3); //prints input, student function, library function, and difference.
        }
    }

    if (t_input == true) {
        printf("  x            arcTan           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double i = 1.0; i < 10.0;
             i += 0.1) { //calls functions from 0.0 to 10.0 incrementing by 0.1
            double C1 = arcTan(i);
            double C2 = atan(i);
            double C3 = C1 - C2;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, C1, C2,
                C3); //prints input, student function, library function, and difference.
        }
    }

    if (l_input == true) {
        printf("  x            Log              Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double j = 1.0; j < 10.0;
             j += 0.1) { //calls functions from 0.0 to 10.0 incrementing by 0.1
            double D1 = Log(j);
            double D2 = log(j);
            double D3 = D1 - D2;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", j, D1, D2,
                D3); //prints input, student function, library function, and difference.
        }
    }
    return 0;
}
