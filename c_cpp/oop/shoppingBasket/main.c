
/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Custom modules */
#include "basket.h"         /* Basket management */
#include "basket_print.h"   /* Basket display */

int main(void)
{
    struct Basket b;
    char rc = 0;
    char shopping = 1;

    /* Initiate random seed */
    srand(time(NULL));

    if ( rc = initBasket(&b, 0), !rc ) {
        printf("Couldn't initialize basket, program abort!\n");
        return -1;
    }

    do {
        printExistingArticles();

        shopping = fillBasket(&b);
    } while (shopping);

    printf("Here's your receip!\n");
    printBasket(&b);

    freeBasket(&b);

    return 0;
}