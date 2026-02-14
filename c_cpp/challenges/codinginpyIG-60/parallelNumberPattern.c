/**
 * Write a program to print below pattern:
 *               1    2    3    4
 *          8    7    6    5
 *     9    10   11   12
 *16   15   14   13
 * */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char **argv) {
        uint32_t n = 4;
        uint32_t i = 0, j = 0, k = 0;

        if (--argc == 1) {
                n = atoi(argv[1]);
        }

        for (j = 0; j < n; j++) {
                /* Spaces pre-fix */
                for (k = n-j-1; k > 0; k--)
                        printf("%*c ", n, ' ');

                if (j % 2) {    /* Odd  lines */
                        for (i = 0; i < n; i++)
                                printf("%-*d ", n, (j+1)*n-i);
                } else {        /* Even lines */
                        for (i = 1; i <= n; i++)
                                printf("%-*d ", n, j*n+i);
                }

                printf("\n");
        }

        return EXIT_SUCCESS;
}
