/**
 * Ref:
 * - https://stackoverflow.com/questions/38767967/clear-input-buffer-after-fgets-in-c
 */

#include "input_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

char buffer[50] = { 0 };
char * p = NULL, * endPtr = NULL;

/* ************************************************************************* */
void clear_remaining_stdin(void) {
        // Overall: Read up to newline
        scanf("%*[^\n]");       /* Read '*', except    '\n' */
        scanf("%*c");           /* Read '*', including '\n' */
}

/* ************************************************************************* */
int readInt(int *i) {
        static long int i_tmp = 0;

        /* *** 1) VALIDATE INPUT *** */
        /* Problem if fgets return NULL */
        if ( ! fgets(buffer, sizeof(buffer), stdin) ) {
                return -1;
        }

        /* If '\n' not found, clear input's remains */
        if (p = strchr(buffer, '\n'), !p) {
                /* TODO: Could have a leading spaces trimming,
                 *       but for now take it as invalid input */

                clear_remaining_stdin();

                /* As there is something left,
                 * we can already tell that the input is invalid */
                return -1;
        }

        /* Replace detected '\n' with '\0' */
        *p = 0;

        /* *** 2) PARSING *** */
        i_tmp = strtof(buffer, &endPtr);

        /* If end of string not reached, then they're something remaining
         * Again, another invalid input */
        if (*endPtr != '\0') {
                return 1;
        }

        /* Out-of-range & errno check */
        if ((i_tmp >= INT_MAX || i_tmp <= INT_MIN) || errno == ERANGE) {
                return 1;
        }

        /* Conversion failed, floating will be 0.f
         * In this case, it is accepted as a result */
        *i = (int)i_tmp;

        return 0;
}

/* ************************************************************************* */
int readFloat(float *f) {
        static float f_tmp = 0.f;

        /* *** 1) VALIDATE INPUT *** */
        /* Problem if fgets return NULL */
        if ( ! fgets(buffer, sizeof(buffer), stdin) ) {
                return -1;
        }

        /* If '\n' not found, clear input's remains */
        if (p = strchr(buffer, '\n'), !p) {
                /* TODO: Could have a leading spaces trimming,
                 *       but for now take it as invalid input */

                clear_remaining_stdin();

                /* As there is something left,
                 * we can already tell that the input is invalid */
                return -1;
        }

        /* Replace detected '\n' with '\0' */
        *p = 0;

        /* *** 2) PARSING *** */
        f_tmp = strtof(buffer, &endPtr);

        /* If end of string not reached, then they're something remaining
         * Again, another invalid input */
        if (*endPtr != '\0') {
                return 1;
        }

        /* Out-of-range & errno check */
        if ((f_tmp == HUGE_VALF || f_tmp == (-HUGE_VALF)) && errno == ERANGE) {
                return 1;
        }

        /* Conversion failed, floating will be 0.f
         * In this case, it is accepted as a result */
        *f = f_tmp;

        return 0;
}
