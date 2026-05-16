/**
 * Ref:
 * - https://stackoverflow.com/questions/38767967/clear-input-buffer-after-fgets-in-c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char buffer[50] = { 0 };
char * p = NULL, * endPtr = NULL;

#define PRINT_ENDL()    printf("\n");

#define PRINT_SIMLPE_TEXT_BOLD(STR)                     \
        do {                                            \
                printf("\033[1m%s\033[0m", STR);        \
        } while (0)

/* Note: If used without a scanf or fgets, it will behave like them.
 *       But your input will simply be lost. */
void clear_remaining_stdin(void) {
        // Overall: Read up to newline
        scanf("%*[^\n]");       /* Read '*', except    '\n' */
        scanf("%*c");           /* Read '*', including '\n' */
}

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
                /* As they are something left,
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

        /* Out-of-range check */
        if (f_tmp == HUGE_VALF || f_tmp == (-HUGE_VALF)) {
                return 1;
        }

        /* Conversion failed, floating will be 0.f
         * In this case, it is accepted as a result */
        *f = f_tmp;

        return 0;
}

int main(void) {
        int rc  = 0;
        float f = 0.f;

        PRINT_SIMLPE_TEXT_BOLD("Reading float...\n");
        if (rc = readFloat(&f), rc > 0) {
                printf("Issue during input validation!\n");
        } else if (rc < 0) {
                printf("Issue during parsing!\n");
        }
        printf("Float: %f\n", f);
        PRINT_ENDL();

        return 0;
}

