/** 
 * @file basket.h
 * 
 * @brief Wrapper around an article "class", in order to fill
 *        an array or articles and create a shopping basket.
 * 
 * For a shopping basket project, this file offers the basket API.
 * It allows to:
 *     - Initiate a basket
 *     - Fill a basket
 *     - Free a basket (destroy content and free article's list)
 */
#ifndef __BASKET_H__
#define __BASKET_H__

#include "articles/article.h"

#include <inttypes.h>

/*****************************************************************************
 * @def DEFAULT_BASKET_SIZE
 * @brief Represent the default basket's size if 0 is entered at init.
 *****************************************************************************/
#define DEFAULT_BASKET_SIZE      4

/*****************************************************************************
 * @def NAME_BUFFER_LENGTH
 * @brief Represent a generic naming buffer length.
 * 
 * @note When declaring an name array with it, don't forget the "+1" for '\0'.
 *****************************************************************************/
#define NAME_BUFFER_LENGTH      50

/*****************************************************************************
 * @struct Basket
 * @brief Represent a basket with articles.
 * 
 * @var Basket::list     Represent the article's list
 * @var Basket::size     Represent the number of articles in basket
 * @var Basket::capacity Represent the basket's capacity
 * 
 * @note When size == capacity, basket is full, so capacity must be increased.
 *       The capacity augmentation is automatically done within fillBasket().
 *****************************************************************************/
struct Basket {
    struct Article **list;
    uint32_t size;
    uint32_t capacity;
};

/*****************************************************************************
 * @brief Basket initialization
 * @param b        Address of an **existing** basket
 * @param capacity Basket's capacity
 * @return 1 on Success, 0 on Failure
 * 
 * @note If capacity is 0, DEFAULT_BASKET_SIZE will be used.
 *****************************************************************************/
char initBasket(struct Basket *b, uint32_t capacity);

/*****************************************************************************
 * @brief Print available articles to be bought.
 *****************************************************************************/
void printExistingArticles(void);

/*****************************************************************************
 * @brief Fill basket with articles of your choice
 * @param b Address of an **existing** basket
 * @return 1 while shopping, else 0 if wanted to checkout.
 *****************************************************************************/
char fillBasket(struct Basket *b);

/*****************************************************************************
 * @brief Free allocated memory for basket
 * @param b Address of an **existing** basket
 *****************************************************************************/
void freeBasket(struct Basket *b);

#endif /* __BASKET_H__ */