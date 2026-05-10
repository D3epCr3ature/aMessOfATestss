
#include "basket_print.h"   /* Associated header */

/* Standard libraries */
#include <stdio.h>
#include <string.h>

/* Custom modules */
#include "articles/article.h"
#include "basket.h"

/** @brief Empty string */
#define EMPTY_STRING            ""

/**
 * @brief Category indexes
 * 
 * Used to order the way to display ticket's informations
 */
enum CATEGORIES_INDEXES { CAT_ARTICLE = 0    , /*CAT_DISCOUNT_PRICE,*/
                          CAT_DISCOUNT_STATUS, CAT_QUANTITY,
                          CAT_UNITPRICE      , CAT_TOTAL };

/*
 * Group of functions that help display category's columns
 * 
 * There's also an array of functions pointer to iterate over them.
 */
void printCategoryArticle(void);
/* TODO: Prepared but not implemented. */
//void printCategoryDiscount(void);
void printCategoryDiscountStatus(void);
void printCategoryQuantity(void);
void printCategoryUnitPrice(void);
void printCategoryTotal(void);
void (*printCategory[])(void) = { printCategoryArticle,
                                  //printCategoryDiscount,
                                  printCategoryDiscountStatus,
                                  printCategoryQuantity,
                                  printCategoryUnitPrice,
                                  printCategoryTotal };

/*
 * Group of functions that help display article's infos
 * 
 * There's also an array of functions pointer to iterate over them.
 */
void printArticle(struct Article *art);
/* TODO: Prepared but not implemented. */
//void printDiscount(struct Article *art);
void printDiscountStatus(struct Article *art);
void printQuantity(struct Article *art);
void printUnitPrice(struct Article *art);
void printTotal(struct Article *art);
void (*printInfo[])(struct Article *art) = { printArticle,
                                             //printDiscount,
                                             printDiscountStatus,
                                             printQuantity,
                                             printUnitPrice,
                                             printTotal };

/**
 * @var Global COLUMNS
 * @brief Use this array to define the printing order of the ticket
 * 
 * @note If you change anything about this array, think about updating
 *       the TICKET_WIDTH_LEN below aswell.
 */
int COLUMNS[] = { CAT_ARTICLE       , CAT_DISCOUNT_STATUS,
                  /*CAT_DISCOUNT_VALUE,*/ CAT_QUANTITY,
                  CAT_UNITPRICE     , CAT_TOTAL };

/** @brief Number of columns to print on ticket */
#define COLUMNS_LEN (sizeof(COLUMNS) / sizeof(*COLUMNS))

/**
 * @brief Represent the COMPLETE length of the ticket, without the borders.
 * 
 * @note If you change anything about the above array "COLUMNS",
 *       you need to match the order and keep only the same length
 *       here aswell.
 */
#define TICKET_WIDTH_LEN        (1 +                        \
                                 ARTICLE_PRINT_LEN    + 1 + \
                                 DISCSTATUS_PRINT_LEN + 1 + \
                                 QTYWEIGHT_PRINT_LEN  + 1 + \
                                 UNITPRICE_PRINT_LEN  + 1 + \
                                 TOTAL_PRINT_LEN      + 1)

/* Here's the Top-[Left|Right] symbol used for the corner.
 * Alongside the Bottom-[Left|Right] symbol too. */
#define TICKET_TL_CORNER        '.'
#define TICKET_TR_CORNER        '.'
#define TICKET_BL_CORNER        '\''
#define TICKET_BR_CORNER        '\''

/* Here's the symbols used for both sides of the ticket. */
#define TICKET_LEFT_SIDE        '\\'
#define TICKET_RIGHT_SIDE       '/'

/* Here's the symbols used for both ends  of the ticket. */
#define TICKET_TOP_SIDE         '~'
#define TICKET_BOT_SIDE         '~'

/*****************************************************************************
 * @private
 * @brief Print the top line of the ticket (1st ever line)
 *****************************************************************************/
void printTopLine(void)
{
    static int i = 0;
    
    printf("%c", TICKET_TL_CORNER);
    for (i = 0; i < TICKET_WIDTH_LEN; i++)
        printf("%c", TICKET_TOP_SIDE);
    printf("%c\n", TICKET_TR_CORNER);
}

/*****************************************************************************
 * @private
 * @brief Print category's section about the article's name
 *****************************************************************************/
void printCategoryArticle(void)
{
    printf("%-*.*s ", ARTICLE_PRINT_LEN, ARTICLE_PRINT_LEN,
                      ARTICLE_PRINT_CAT);
}

/*****************************************************************************
 * @private
 * @brief Print category's section about the article's discount value
 * 
 * @note TODO: Not implemented on the article's side, because not thought of it
 *             during dev. So it is only prepared for implementation.
 *****************************************************************************/
void printCategoryDiscount(void)
{
    printf("%-*.*s ", DISCPRICE_PRINT_LEN, DISCPRICE_PRINT_LEN,
                      DISCPRICE_PRINT_CAT);
}

/*****************************************************************************
 * @private
 * @brief Print category's section about the article's discount status
 *****************************************************************************/
void printCategoryDiscountStatus(void)
{
    printf("%-*.*s ", DISCSTATUS_PRINT_LEN, DISCSTATUS_PRINT_LEN,
                      DISCSTATUS_PRINT_CAT);
}

/*****************************************************************************
 * @private
 * @brief Print category's section about the article's quantity
 *****************************************************************************/
void printCategoryQuantity(void)
{
    printf("%-*.*s ", QTYWEIGHT_PRINT_LEN, QTYWEIGHT_PRINT_LEN,
                      QUANTITY_PRINT_CAT);
}

/*****************************************************************************
 * @private
 * @brief Print category's section about the article's unit price
 *****************************************************************************/
void printCategoryUnitPrice(void)
{
    printf("%-*.*s ", UNITPRICE_PRINT_LEN, UNITPRICE_PRINT_LEN,
                      UNITPRICE_PRINT_CAT);
}

/*****************************************************************************
 * @private
 * @brief Print category's section about the article's total price
 *****************************************************************************/
void printCategoryTotal(void)
{
    printf("%-*.*s ", TOTAL_PRINT_LEN, TOTAL_PRINT_LEN,
                      TOTAL_PRINT_CAT);
}

/*****************************************************************************
 * @private
 * @brief Print category's ticket line
 *****************************************************************************/
void printCategoriesLine(void)
{
    static int i = 0;
    
    printf("%c ", TICKET_LEFT_SIDE);

    for (i = 0; i < COLUMNS_LEN; i++) {
        printCategory[COLUMNS[i]]();
    }

    printf("%c\n", TICKET_RIGHT_SIDE);
}

/*****************************************************************************
 * @private
 * @brief Print article's name column
 *****************************************************************************/
void printArticle(struct Article *art)
{
    if (strlen(Article_GETNAME(art)) <= (ARTICLE_PRINT_LEN-3)) {
        /* Fully print article's name .. */
        printf("%-*.*s ", ARTICLE_PRINT_LEN, ARTICLE_PRINT_LEN,
                          Article_GETNAME(art));

    } else {
        /* .. or truncate, because name too long. */
        printf("%-*.*s... ", ARTICLE_PRINT_LEN-3, ARTICLE_PRINT_LEN-3,
                             Article_GETNAME(art));
    }
}

/*****************************************************************************
 * @private
 * @brief Print article's discount value column
 * 
 * @note TODO: Not implemented on the article's side, because not thought of it
 *             during dev. So it is only prepared for implementation.
 *             Implement Article_GETDISCOUNTPRICE()
 *****************************************************************************/
void printDiscount(struct Article *art)
{
    printf("%*.*f ", DISCPRICE_PRINT_LEN, DISCPRICE_DEC_PRINT_LEN,
                     /*Article_GETDISCOUNTPRICE(art)*/ 0.f);
}

/*****************************************************************************
 * @private
 * @brief Print article's discount status column
 *****************************************************************************/
void printDiscountStatus(struct Article *art)
{
    printf("%-*.*s ", DISCSTATUS_PRINT_LEN, DISCSTATUS_PRINT_LEN,
                      Article_GETDISCOUNTSTATUS(art) ? 
                                DISCSTATUS_PRINT_CAT : EMPTY_STRING);
}

/*****************************************************************************
 * @private
 * @brief Print article's quantity column
 * 
 * @note It manages if the article uses Quantity as integer or
 *       Weight, being a float.
 *       It also uses "NaN", if by any chance either of the function is defined.
 *****************************************************************************/
void printQuantity(struct Article *art)
{
    if ( art->funcTable->getQuantity ) {
        printf("%*d ", QTYWEIGHT_PRINT_LEN,
                       Article_GETQUANTITY(art));

    } else if ( art->funcTable->getWeight ) {
        printf("%*.*f ", QTYWEIGHT_PRINT_LEN, WEIGHT_DEC_PRINT_LEN,
                         Article_GETWEIGHT(art));

    } else {
        printf("%*s ", QTYWEIGHT_PRINT_LEN, "NaN");
    }
}

/*****************************************************************************
 * @private
 * @brief Print article's unit price column
 *****************************************************************************/
void printUnitPrice(struct Article *art)
{
    printf("%*.*f ", UNITPRICE_PRINT_LEN, UNITPRICE_DEC_PRINT_LEN,
                     Article_GETUNITPRICE(art));
}

/*****************************************************************************
 * @private
 * @brief Print article's total price column
 *****************************************************************************/
void printTotal(struct Article *art)
{
    printf("%*.*f ", TOTAL_PRINT_LEN, TOTAL_DEC_PRINT_LEN,
                     Article_GETTOTALPRICE(art));
}

/*****************************************************************************
 * @private
 * @brief Print complete article's infos ticket line
 *****************************************************************************/
void printArticleLine(struct Article *art, int line)
{
    static int i = 0;
    
    printf("%c ", line % 2 ? TICKET_LEFT_SIDE : TICKET_RIGHT_SIDE);

    if (Article_GETDISCOUNTSTATUS(art)) {
        printf("\033[1m"); /* Article line to BOLD if has discount. */
    }

    /* "i" access causes a */
    for (i = 0; i < COLUMNS_LEN; i++) {
        printInfo[COLUMNS[i]](art);
    }

    printf("\033[0m" /* Remove Bold effect */
           "%c\n", line % 2 ? TICKET_RIGHT_SIDE : TICKET_LEFT_SIDE);
}

/*****************************************************************************
 * @private
 * @brief Print empty line between the last article and the basket's total.
 *****************************************************************************/
void printSplitContentAndTotal(int line)
{
    if (line % 2) {
        printf("%c%*.*s%c\n", TICKET_LEFT_SIDE,
                            TICKET_WIDTH_LEN, TICKET_WIDTH_LEN,
                            EMPTY_STRING, TICKET_RIGHT_SIDE);
    } else {
        printf("%c%*.*s%c\n", TICKET_RIGHT_SIDE,
                            TICKET_WIDTH_LEN, TICKET_WIDTH_LEN,
                            EMPTY_STRING, TICKET_LEFT_SIDE);
    }
}

/*****************************************************************************
 * @private
 * @brief Print basket's total price line.
 * 
 * @note "-3" is from the in-between spaces:
 *       - 1) Left corner          -> Col#1 (Total string)
 *       - 2) Col#1 (Total string) -> Col#2 (Total price)
 *       - 3) Col#2 (Total price)  -> Right corner
 *****************************************************************************/
void printTotalLine(float total, int line)
{
    if (line % 2) {
        printf("%c %-*.*s %*.*f %c\n", TICKET_LEFT_SIDE,
                                       TICKET_WIDTH_LEN -
                                            FLOAT_PRINT_LEN - 3,
                                       TICKET_WIDTH_LEN -
                                            FLOAT_PRINT_LEN - 3, "Total",
                                       FLOAT_PRINT_LEN,
                                            FLOAT_DEC_PRINT_LEN, total,
                                       TICKET_RIGHT_SIDE);
    } else {
        printf("%c %-*.*s %*.*f %c\n", TICKET_RIGHT_SIDE,
                                       TICKET_WIDTH_LEN -
                                            FLOAT_PRINT_LEN - 3,
                                       TICKET_WIDTH_LEN -
                                            FLOAT_PRINT_LEN - 3, "Total",
                                       FLOAT_PRINT_LEN,
                                            FLOAT_DEC_PRINT_LEN, total,
                                       TICKET_LEFT_SIDE);
    }
}

/*****************************************************************************
 * @private
 * @brief Print the bottom line of the ticket (last ever line)
 *****************************************************************************/
void printBottomLine(void)
{
    static int i = 0;
    
    printf("%c", TICKET_BL_CORNER);

    for (i = 0; i < TICKET_WIDTH_LEN; i++)
        printf("%c", TICKET_BOT_SIDE);

    printf("%c\n", TICKET_BR_CORNER);
}

/* ************************************************************************* */
void printBasket(struct Basket *b)
{
    static int   i = 0;
    static float totalPrice = 0.f;

    /* Check on basket existence */
    if ( !b ) {
        return;
    }
    
    printTopLine();
    printCategoriesLine();

    /* *** BASKET CONTENT ********* */
    totalPrice = 0.f;   /* Reset basket's price */

    for (i = 0; i < b->size; i++) {
        printArticleLine(b->list[i], i);

        /* Accumulate basket's price */
        totalPrice += Article_GETTOTALPRICE(b->list[i]);
    }

    printSplitContentAndTotal(i++);
    printTotalLine(totalPrice, i++);
    printBottomLine();

    if (b->size) {  /* Pleasant goodbye message */
        printf(">>> Thanks for your purchase! :D\n");
    } else {        /* Sorry    goodbye message */
        printf(">>> Hope we'll get what you needed soon. :/\n");
    }
}