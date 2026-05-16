
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_DISPLAY_LENGTH   26
#define HYPEN_COMPLETE_LINE     "---------------------------------------------"

int main(void) {
        char i = 0;
        char string[] = "a +/- long string";

        printf(">>> Format: \"%%.*s\" %*.*s.\n",
               STRING_DISPLAY_LENGTH-14, STRING_DISPLAY_LENGTH-14,
               HYPEN_COMPLETE_LINE);
        for (i = 0; i < sizeof(string); i++)
                printf("%2d) %.*s |\n", i, i, string);

        printf(">>> Format: \"%%*.*s\" %*.*s.\n",
               STRING_DISPLAY_LENGTH-15, STRING_DISPLAY_LENGTH-15,
               HYPEN_COMPLETE_LINE);
        for (i = 0; i < sizeof(string); i++)
                printf("%2d) %*.*s |\n", i, STRING_DISPLAY_LENGTH, i, string);

        printf(">>> Format: \"%%-*.*s\" %*.*s.\n",
               STRING_DISPLAY_LENGTH-16, STRING_DISPLAY_LENGTH-16,
               HYPEN_COMPLETE_LINE);
        for (i = 0; i < sizeof(string); i++)
                printf("%2d) %-*.*s |\n", i, STRING_DISPLAY_LENGTH, i, string);

        return 0;
}

/* Output of above code:
>>> Format: "%.*s" ------------.
 0)  |
 1) a |
 2) a  |
 3) a + |
 4) a +/ |
 5) a +/- |
 6) a +/-  |
 7) a +/- l |
 8) a +/- lo |
 9) a +/- lon |
10) a +/- long |
11) a +/- long  |
12) a +/- long s |
13) a +/- long st |
14) a +/- long str |
15) a +/- long stri |
16) a +/- long strin |
17) a +/- long string |
>>> Format: "%*.*s" -----------.
 0)                            |
 1)                          a |
 2)                         a  |
 3)                        a + |
 4)                       a +/ |
 5)                      a +/- |
 6)                     a +/-  |
 7)                    a +/- l |
 8)                   a +/- lo |
 9)                  a +/- lon |
10)                 a +/- long |
11)                a +/- long  |
12)               a +/- long s |
13)              a +/- long st |
14)             a +/- long str |
15)            a +/- long stri |
16)           a +/- long strin |
17)          a +/- long string |
>>> Format: "%-*.*s" ----------.
 0)                            |
 1) a                          |
 2) a                          |
 3) a +                        |
 4) a +/                       |
 5) a +/-                      |
 6) a +/-                      |
 7) a +/- l                    |
 8) a +/- lo                   |
 9) a +/- lon                  |
10) a +/- long                 |
11) a +/- long                 |
12) a +/- long s               |
13) a +/- long st              |
14) a +/- long str             |
15) a +/- long stri            |
16) a +/- long strin           |
17) a +/- long string          |
*/
