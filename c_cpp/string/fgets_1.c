
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PRINT_ENDL()    printf("\n");

#define PRINT_SIMLPE_TEXT_BOLD(STR)                     \
        do {                                            \
                printf("\033[1m%s\033[0m", STR);        \
        } while (0)

/* Note: If used without a scanf or fgets, it will behave like them.
 *       But your input will simply be lost. */
void clear_remaining_stdin_1(void) {
        char ch = 0;
        while ( ((ch = getchar()) != EOF) && (ch != '\n') ) /* Nothing */ ;
}

/* Note: If used without a scanf or fgets, it will behave like them.
 *       But your input will simply be lost. */
void clear_remaining_stdin_2(void) {
        // Overall: Clear up to newline
        scanf("%*[^\n]");       /* Read '*', except    '\n' */
        scanf("%*c");           /* Read '*', including '\n' */
}

int main(void) {
        char quitBuff[5] = "quit";
        char buffer[50] = { 0 };
        int  clearFnUsed = 0;
        char *p = NULL;
        int  i = 0;

        PRINT_SIMLPE_TEXT_BOLD("User-input loop (quit to exit program)\n");
        printf("Quick note: Input buffer is limited to 50 chars.\n");
        do {
                printf("Input?\n");
                if ( ! fgets(buffer, sizeof(buffer), stdin) ) {
                        printf("Issue with input...\n");
                        continue;
                }

                PRINT_SIMLPE_TEXT_BOLD("> Detecting '\\n' in buffer\n");
                if (p = strchr(buffer, '\n'), !p) {
                        printf(">> '\\n' Not found, clearing input...\n");
                        if (clearFnUsed % 2) {  clear_remaining_stdin_1(); }
                        else                 {  clear_remaining_stdin_2(); }
                        continue;
                }

                printf(">> '\\n' Found, replacing it with '\\0'\n");
                *p = 0;

                printf("\033[1mEntered:\033[0m %s\n", buffer);

                PRINT_SIMLPE_TEXT_BOLD("> User-input length == "
                                       "quit msg length?\n");
                if (strlen(buffer) != sizeof(quitBuff)-1) {
                        printf(">> Lengths differ.\n");
                        continue;
                }

                /* User-input to lower case, in order to detect every variant */
                printf(">> Lengths are matching.\n");
                PRINT_SIMLPE_TEXT_BOLD("> Checking quit msg...\n");
                for (i = 0; i < sizeof(quitBuff)-1; i++) {
                        quitBuff[i] = tolower(buffer[i]);
                }
                if ( ! strncmp(quitBuff, "quit", sizeof(quitBuff)-1) ) {
                        PRINT_SIMLPE_TEXT_BOLD("Leaving loop!\n");
                        break;
                }
        } while (1);

        return 0;
}

