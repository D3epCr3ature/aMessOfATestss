/**
 * Write a program to give the following output for a given input:
 *
 * Example 1:
 * Input: 3[a]2[bc]
 * Ouput: aaabcbc
 *
 * Example 2:
 * Input: 3[a2[c]]
 * Ouput: accaccacc
 *
 * Hypothesis: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * - input is always well formatted
 * - no number in pattern
 *   To adjust that, split the repetition detection
 *
 * Recursive approach: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * - IF string starts with number
 *      - Read pattern block repetition
 * - ELIF pattern character
 *      - print character
 * - ELIF end of pattern block 
 *      - Return the following character's address,
 *        in order to identifying next block pattern
 * - ELIF end of input
 *      - Return it
 *
 * - LOOP Current block repetition
 *      - recursion call with current char ptr + 1
 *
 * - IF current ptr is on '[' at this point,
 *   it means we've ended a block pattern
 *      - recursion call with end of last block pattern ptr
 *
 * - END end of last block pattern ptr to the top!
 *
 * Note: ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * - Modification(s): Pass repeat as paramater
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_MODULE_IS   "pattern_print"
//#define DEBUG_LEVEL     LOG_LVL_DEBUG
#include "../../utils/log.h"

//#define WITH_EXPECTATION        1
#if defined(WITH_EXPECTATION)
char buff[500]  = {0};
int filling_idx = 0;

#define EXPECTATION_VARS_RESET  \
buff[filling_idx++] = '\0';     \
filling_idx = 0

#define PRINT_RESULT(END_PTR, EXPECTION_BUFFER)                         \
do {                                                                    \
        if (*END_PTR == '\0' && (! strcmp(buff, EXPECTION_BUFFER))) {   \
                LOGI("Properly analysed and matching expectation!\n");  \
        }                                                               \
} while (0)
#else
#define EXPECTATION_VARS_RESET  (void)0

#define PRINT_RESULT(END_PTR, EXPECTION_BUFFER)                         \
do {                                                                    \
        if (*END_PTR == '\0') {                                         \
                LOGI("Properly analysed!\n");                           \
        }                                                               \
} while (0)
#endif

void help_msg(void) {
        printf("usage: ./repPattern.elf [PATTERN] [PATTERN_EXPECTATION]\n");
        printf("       PATTERN             : Compressed form pattern\n"
               "                             Examples: 3[a]2[bc]\n"
               "                                     : 4[a2[zd]]\n");
        printf("       PATTERN_EXPECTATION : Full form expected pattern\n"
               "                             Examples: aaabcbc\n"
               "                             Examples: azdzdazdzdazdzdazdzd\n");
        printf("       Note: If nothing is specified, the program will run \n"
               "             sample conversions.\n");
        printf("             You can only specify the PATTERN argument and\n"
               "             the program will generate its full form.\n");
}

char * pattern_print(char * string) {
        LOGD("Call with: %s\n", string);
        int repeat = 1, sscanf_rc = 0;
        char *ptr  = string;
        char *endPattern = NULL;

        /* Number detected ? */
        if (*ptr >= '0' && *ptr <= '9') {
                /* Try reading it, followed by a '[' */
                sscanf_rc = sscanf(string, "%d[", &repeat);
                if ( ! sscanf_rc ) {
                        LOGE("Bad Input: Number not followed by '['");
                        return NULL;
                }

                /* Look for the '[' in order to skip the repetition number */
                ptr = strstr(string, "[");
                LOGD("Identify \"repeat\" = %d\n", repeat);
        /* Alpha char detected ? */
        } else if (*ptr >= 'a' && *ptr <= 'z') {
                LOGD("Character: %c\n", *ptr);
#if defined(WITH_EXPECTATION)
                /* Fill buffer with current char */
                buff[filling_idx++] = *ptr;
#endif
                /* Print it */
                printf("%c", *ptr);
        /* Closing bracket detected ? */
        } else if (*ptr == ']') {
                LOGD("DEPTH END: Returns: %s\n", ptr+1);
                /* Return following position to continue with next block */
                return ptr+1;
        /* End of input detected ? */
        } else if (*ptr == '\0') {
                /* Return it to properly end the conversion */
                return ptr;
        }

        /* Repeat current block pattern */
        while ( repeat-- ) {
                LOGD("REPEAT: %d\n", repeat);
                endPattern = pattern_print(ptr+1);
        }

        /* Identify following block pattern if there is any */
        if (*ptr == '[') {
                LOGD("Identifying next pattern block: %s\n", endPattern);
                endPattern = pattern_print(endPattern);
        }

        return endPattern;
}

int main(int argc, char **argv) {
        int i = 0;
        char * endPtr = NULL;
        // Inputs
        char str1[] = "3[a]2[bc]";
        char str2[] = "3[a2[c]]";
        char str3[] = "23[a]2[b]3[2[ac]]";
        char str4[] = "2[3[a]2[b]]3[2[ac]]5[yz]";
        char str5[] = "2[3[a]2[b]z]3[2[ac]]5[yz]";
        // Expectations
#if defined(WITH_EXPECTATION)
        char str1_expectation[] = "aaabcbc";
        char str2_expectation[] = "accaccacc";
        char str3_expectation[] = "aaaaaaaaaaaaaaaaaaaaaaabbacacacacacac";
        char str4_expectation[] = "aaabbaaabbacacacacacacyzyzyzyzyz";
        char str5_expectation[] = "aaabbzaaabbzacacacacacacyzyzyzyzyz";
#endif

        for ( ; i < argc; i++) {
                if ((!strcmp(argv[i], "-h")) || (!strcmp(argv[i], "--help"))) {
                        help_msg();
                        return 0;
                }
        }

        if (argc != 1) {
                /* ~~~ CONVERSION FROM USER'S INPUT ~~~ */
                printf("Input   : %s\n", argv[1]);
                endPtr = pattern_print(argv[1]);
                printf("\n");
                if (argc == 3)
                        PRINT_RESULT(endPtr, argv[2]);
                else
                        PRINT_RESULT(endPtr, (char *)0xDEADBEEF);
        } else {
                /* ~~~ SAMPLE CONVERSIONS ~~~ */
                printf("String 1: %s\n", str1);
                endPtr = pattern_print(str1);
                printf("\n");
                EXPECTATION_VARS_RESET;
                PRINT_RESULT(endPtr, str1_expectation);

                printf("\nString 2: %s\n", str2);
                endPtr = pattern_print(str2);
                printf("\n");
                EXPECTATION_VARS_RESET;
                PRINT_RESULT(endPtr, str2_expectation);

                printf("\nString 3: %s\n", str3);
                endPtr = pattern_print(str3);
                printf("\n");
                EXPECTATION_VARS_RESET;
                PRINT_RESULT(endPtr, str3_expectation);

                printf("\nString 4: %s\n", str4);
                endPtr = pattern_print(str4);
                printf("\n");
                EXPECTATION_VARS_RESET;
                PRINT_RESULT(endPtr, str4_expectation);

                printf("\nString 5: %s\n", str5);
                endPtr = pattern_print(str5);
                printf("\n");
                EXPECTATION_VARS_RESET;
                PRINT_RESULT(endPtr, str5_expectation);
        }

        printf("\n");
        return 0;
}
