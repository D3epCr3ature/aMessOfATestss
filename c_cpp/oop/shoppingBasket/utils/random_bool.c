
#include "random_bool.h"    /* Associated header */

/* Standard libraries */
#include <stdlib.h>

/* ************************************************************************* */
char rand_bool(char bit)
{
    if (bit % 2) {  /* Bit is odd */
        return (((rand() + 0xDEADBEEF) % 997) >> bit) & 1;
    }

    /* Bit is even, like boobs */
    return (((rand() + 0xB00B5) ^ 997) >> bit) & 1;
}