/** 
 * @file basket_print.h
 * 
 * @brief Print a basket with its content and total price, like a receipe.
 * 
 * @note All possible columns::
 *       - Article, Discount (Price), Discount (Status), 
 *         Quantity, Unit Price, Total Price
 * 
 * For a shopping basket project, this file offers
 * the function to print a basket's content.
 * It is isolated to separate the management API and the display.
 * Plus, the display can be quite complicated if you want to fancy it.
 * So it is better to have it separated, also for that reason.
 */
#ifndef __BASKET_PRINT_H__
#define __BASKET_PRINT_H__

#include "basket.h"

/*****************************************************************************
 * @def FLOAT_PRINT_LENGTH
 * @brief Represent the length on which we display a **float**.
 *        (Format length)
 * 
 * @note 5 + '.' => 6 characters
 *****************************************************************************/
#define FLOAT_PRINT_LEN          6

/*****************************************************************************
 * @def FLOAT_DEC_PRINT_LENGTH
 * @brief Represent the length on which we display
 *        the **floating part** of a **float**.
 *        (Format length)
 * 
 * @example Define set to 2: 123.456 => Will be displayed as 123.46
 *****************************************************************************/
#define FLOAT_DEC_PRINT_LEN      2



/*****************************************************************************
 * @def ARTICLE_PRINT_CAT[egory]
 * @brief Represent the artcile's column name
 *****************************************************************************/
#define ARTICLE_PRINT_CAT       "Article"

/*****************************************************************************
 * @def ARTICLE_PRINT_LENGTH
 * @brief Represent the length on which we display an **article**.
 *        (Format length)
 *****************************************************************************/
#define ARTICLE_PRINT_LEN       15



/*****************************************************************************
 * @def DISCPRICE_PRINT_CAT[egory]
 * @brief Represent the discount's column name
 *****************************************************************************/
#define DISCPRICE_PRINT_CAT     "Discount"

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define DISCPRICE_PRINT_LEN     FLOAT_PRINT_LEN

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define DISCPRICE_DEC_PRINT_LEN FLOAT_DEC_PRINT_LEN



/*****************************************************************************
 * @def DISCOUNT_PRINT_INFO
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define DISCSTATUS_PRINT_CAT    "[D]"

/*****************************************************************************
 * @def DISCOUNT_PRINT_LENGTH
 * @brief Represent the length on which we display
 *        the discount status.
 *        (Format length)
 *****************************************************************************/
#define DISCSTATUS_PRINT_LEN    ((int)(sizeof(DISCSTATUS_PRINT_CAT)-1))



/*****************************************************************************
 * @def DISCPRICE_PRINT_CAT[egory]
 * @brief Represent the discount's column name
 *****************************************************************************/
#define QUANTITY_PRINT_CAT      "Qty"

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define QTYWEIGHT_PRINT_LEN     FLOAT_PRINT_LEN

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define WEIGHT_DEC_PRINT_LEN    FLOAT_DEC_PRINT_LEN



/*****************************************************************************
 * @def DISCPRICE_PRINT_CAT[egory]
 * @brief Represent the discount's column name
 *****************************************************************************/
#define UNITPRICE_PRINT_CAT     "CHF/Qty"

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define UNITPRICE_PRINT_LEN     ((int)(sizeof(UNITPRICE_PRINT_CAT)-1))

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define UNITPRICE_DEC_PRINT_LEN FLOAT_DEC_PRINT_LEN



/*****************************************************************************
 * @def DISCPRICE_PRINT_CAT[egory]
 * @brief Represent the discount's column name
 *****************************************************************************/
#define TOTAL_PRINT_CAT         "Total"

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define TOTAL_PRINT_LEN         FLOAT_PRINT_LEN

/*****************************************************************************
 * @def DISCPRICE_PRINT_LENGTH
 * @brief Represent how the discount status is displayed on ticket.
 *        (Format)
 *****************************************************************************/
#define TOTAL_DEC_PRINT_LEN     FLOAT_DEC_PRINT_LEN



/*****************************************************************************
 * @brief Print basket's content on a ticket-like view
 * @param b Address of an **existing** basket
 *****************************************************************************/
void printBasket(struct Basket *b);

#endif /* __BASKET_PRINT_H__ */