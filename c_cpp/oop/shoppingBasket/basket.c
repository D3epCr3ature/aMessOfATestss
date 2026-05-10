/**
 * @file basket.c
 * 
 * @note Some message error are just funny.
 *       Why? 
 *          - Because the main purpose of this project is
 *            not the error management issue.
 *          - Plus, when writing it, what I had in mind is a automaton
 *            that could tell you what's wrong with your human interactions.
 * 
 *       If anything, I put some analogy near some messages.
 */

#include "basket.h" /* Associated header */

/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Custom modules */
#include "articles/banana.h"
#include "articles/cheese.h"
#include "articles/drink.h"
#include "articles/meat.h"
#include "articles/pepper.h"
#include "articles/tomato.h"
#include "../../utils/input_reader.h"

/*****************************************************************************
 * @var Global temporary **integer** for some input reading operations.
 * @note I evaluated this var. that, depending on your usage,
 *       might be redeclared at each calls.
 *       So to avoid the multiple declaration overall, it has been set global.
 *       Plus, it can be done here, because there's is no nested call
 *       of the variable (not used -> fn call -> also used in called fn).
 *****************************************************************************/
int          i_tmp = 0;

/*****************************************************************************
 * @var Global temporary **float** for some input reading operations.
 * @note I evaluated this var. that, depending on your usage,
 *       might be redeclared at each calls.
 *       So to avoid the multiple declaration overall, it has been set global.
 *       Plus, it can be done here, because there's is no nested call
 *       of the variable (not used -> fn call -> also used in called fn).
 *****************************************************************************/
float        f_tmp = 0.f;

/*****************************************************************************
 * @var Global **quantity** for some parsing operations.
 * @note I evaluated this var. that, depending on your usage,
 *       might be redeclared at each calls.
 *       So to avoid the multiple declaration overall, it has been set global.
 *       Plus, it can be done here, because there's is no nested call
 *       of the variable (not used -> fn call -> also used in called fn).
 *****************************************************************************/
unsigned int qty = 0;

/*****************************************************************************
 * @var Global **weight** for some parsing operations.
 * @note I evaluated this var. that, depending on your usage,
 *       might be redeclared at each calls.
 *       So to avoid the multiple declaration overall, it has been set global.
 *       Plus, it can be done here, because there's is no nested call
 *       of the variable (not used -> fn call -> also used in called fn).
 *****************************************************************************/
float        weight = 0.f;

/*****************************************************************************
 * @var Global **name** for some reading operations.
 * @note I evaluated this var. that, depending on your usage,
 *       might be redeclared at each calls.
 *       So to avoid the multiple declaration overall, it has been set global.
 *       Plus, it can be done here, because there's is no nested call
 *       of the variable (not used -> fn call -> also used in called fn).
 *****************************************************************************/
char         name[NAME_BUFFER_LENGTH+1] = { 0 };

/*****************************************************************************
 * @enum SHOPPING_ARTICLE
 * @brief Indexes for article selection.
 *****************************************************************************/
enum SHOPPING_ARTICLE { SHOPPING_REPEAT = (-1), SHOPPING_STOPPED = 0,
                        SHOPPING_BANANA       , SHOPPING_PEPPER,
                        SHOPPING_TOMATO       , SHOPPING_MEAT,
                        SHOPPING_CHEESE       , SHOPPING_DRINK };

/*****************************************************************************
 * @var Global article string types
 * 
 * @important Order must match with enum SHOPPING_ARTICLE.
 * 
 * @note Keep the 1st NULL, to keep SHOPPING_STOPPED at index 0.
 *****************************************************************************/
char *articleTypes[] = { "Go to checkout",
                         "Banana", "Pepper", "Tomato",
                         "Meat"  , "Cheese", "Drink",
                         NULL };

/*****************************************************************************
 * @def ARTICLE_MAX_LIMIT
 * @brief Max limit for article selection
 * 
 * @important Max limit must match with highest value of enum SHOPPING_ARTICLE.
 *****************************************************************************/
#define ARTICLE_MAX_LIMIT   SHOPPING_DRINK

/* ************************************************************************* */
char initBasket(struct Basket *b, uint32_t capacity)
{
    /* Check basket's existence */
    if ( !b ) {
        printf("You didn't take a basket!\n");
        return 0;
    }

    /* Set capacity if possible & Set size */
    b->capacity = capacity ? capacity : DEFAULT_BASKET_SIZE;
    b->size = 0;

    /* Allocate article's list */
    b->list = (struct Article **) malloc(sizeof(struct Article *) * b->capacity);

    return (b->list == NULL ? 0 : 1);
}

/* ************************************************************************* */
void freeBasket(struct Basket *b)
{
    static uint32_t i = 0;
    
    /* Check basket & list's existences */
    if ( !b || !b->list ) {
        printf("You didn't take a basket!\n");
        return;
    }

    for (i = 0; i < b->size; i++)
        Article_DESTROY(b->list[i]);
    
    free(b->list);
}

/* ************************************************************************* */
void printExistingArticles(void)
{
    static uint32_t i = 0;
    
    printf("Article at disposal:\n");
    printf(" <0) Re-print articles selection\n");

    for (i = 0; i <= ARTICLE_MAX_LIMIT; i++) {
        printf("%3d) %s\n", i, articleTypes[i]);
    }

    printf("...) More to come soon.\n"  /* Fancy line only :D */
           "     Or feel free to add your own now! ;)\n\n");

    printf("Your choice?\n");
}

/*****************************************************************************
 * @private
 * @brief Read and Check user input to choose an article to buy
 *****************************************************************************/
int16_t chooseArticle(void)
{
    if (readInt(&i_tmp)) {
        /* Invalid input or negative article -> SHOPPING_REPEAT */
        return SHOPPING_REPEAT;
    }

    if (i_tmp > ARTICLE_MAX_LIMIT) {
        /* Asked for yet non-existent article -> SHOPPING_REPEAT */
        return SHOPPING_REPEAT;
    }

    return (int16_t) i_tmp;
}

/*****************************************************************************
 * @private
 * @brief Read a string to be used as a article's name
 * @param name Destination
 * @param len  Tolerated string length
 * @return 0 on Success, -1 on Failure.
 * 
 * @note Tailing spaces are counted as an invalid input.
 *****************************************************************************/
int readString(char *name, int len)
{
    static char * p      = NULL/*,
                * endPtr = NULL*/;

    /* *** 1) VALIDATE INPUT *** */
    /* Problem if fgets return NULL */
    if ( ! fgets(name, len, stdin) ) {
            //name = NULL;
            *name = '\0';
            return -1;
    }

    /* If '\n' not found, clear input's remains */
    if (p = strchr(name, '\n'), !p) {
            /* TODO: Could have a leading spaces trimming,
                *       but for now take it as invalid input */

            clear_remaining_stdin();

            *name = '\0';

            /* As there is something left,
                * we can already tell that the input is invalid */
            return -1;
    }

    /* Replace detected '\n' with '\0' */
    *p = 0;

    return 0;
}

/*****************************************************************************
 * @private
 * @brief Read name
 * 
 * @note Invalidate name on Failure by setting the 1st char to '\0'.
 *****************************************************************************/
void askName(char *name, int len)
{
    if (readString(name, len)) {
        /* Invalid input or negative weight -> Nullify name */
        *name = '\0';
    }
}

/*****************************************************************************
 * @private
 * @brief Read quantity
 * 
 * @note Invalidate quantity on Failure by setting the qty to 0.
 *****************************************************************************/
void askQuantity(unsigned int *qty)
{
    printf("\033[1mQuantity?\033[0m " /* Bold part */
           "(<= 0 means you put the article back)\n");

    if (readInt(&i_tmp) || i_tmp <= 0) {
        /* Invalid input or negative weight -> set quantity to 0 */
        *qty = 0;
    } else {
        *qty = (unsigned int) i_tmp;
    }
}

/*****************************************************************************
 * @private
 * @brief Read weight
 * 
 * @note Invalidate weight on Failure by setting the weight to 0.f.
 *****************************************************************************/
void askWeight(float *weight)
{
    printf("\033[1mWeight?\033[0m " /* Bold part */
           "(<= 0.0 means you put the article back)\n");

    if (readFloat(&f_tmp) || f_tmp < 0.f) {
        /* Invalid input or negative weight -> set weight to 0 */
        *weight = 0.f;
    } else {
        *weight = f_tmp;
    }
}

/*****************************************************************************
 * @private
 * @brief Initiate a Banana, on Success
 *        Otherwise, return NULL
 *****************************************************************************/
//struct Article * addBananaToBasket(void)
struct Article * takeBanana(void)
{
    askWeight(&weight);

    /* Negative weight <=> Leave the article.
    *  (Like not wanting it last minute) */
    if (weight <= 0.f)
        return NULL;

    return Banana_init(weight);
}

/*****************************************************************************
 * @private
 * @brief Initiate a Cheese, on Success
 *        Otherwise, return NULL
 *****************************************************************************/
struct Article * takeCheese(void)
{
    printf("\033[1mCheese's name?\033[0m "); /* Bold part */

    askName(name, NAME_BUFFER_LENGTH);

    /* TODO: Fully let control on cheese naming
     *       Except for the length that can trigger an issue,
     *       in which case, a default name will be used */

    askWeight(&weight);

    /* Negative weight <=> Leave the article.
    *  (Like not wanting it last minute) */
    if (weight <= 0.f)
        return NULL;

    return Cheese_init(*name ? name : CHEESE_DEFAULT_NAME, weight);
}

/*****************************************************************************
 * @private
 * @brief Initiate a Drink, on Success
 *        Otherwise, return NULL
 *****************************************************************************/
struct Article * takeDrink(void)
{
    printf("\033[1mDrink's name?\033[0m "); /* Bold part */

    askName(name, NAME_BUFFER_LENGTH);

    /* TODO: Fully let control on drink naming
     *       Except for the length that can trigger an issue,
     *       in which case, a default name will be used */

    askQuantity(&qty);

    /* Negative weight <=> Leave the article.
    *  (Like not wanting it last minute) */
    if (qty == 0)
        return NULL;

    return Drink_init(*name ? name : DRINK_DEFAULT_NAME, qty);
}

/*****************************************************************************
 * @private
 * @brief Initiate a Meat, on Success
 *        Otherwise, return NULL
 *****************************************************************************/
struct Article * takeMeat(void)
{
    printf("\033[1mMeat's type?\033[0m "); /* Bold part */

    askName(name, NAME_BUFFER_LENGTH);

    /* TODO: Fully let control on meat naming
     *       Except for the length that can trigger an issue,
     *       in which case, a default name will be used */

    askWeight(&weight);

    /* Negative weight <=> Leave the article.
    *  (Like not wanting it last minute) */
    if (weight <= 0.f)
        return NULL;

    return Meat_init(*name ? name : MEAT_DEFAULT_NAME, weight);
}

/*****************************************************************************
 * @private
 * @brief Initiate a Pepper, on Success
 *        Otherwise, return NULL
 *****************************************************************************/
struct Article * takePepper(void)
{
    askWeight(&weight);

    /* Negative weight <=> Leave the article.
    *  (Like not wanting it last minute) */
    if (weight <= 0.f)
        return NULL;

    return Pepper_init(weight);
}

/*****************************************************************************
 * @private
 * @brief Initiate a Tomato, on Success
 *        Otherwise, return NULL
 *****************************************************************************/
struct Article * takeTomato(void)
{
    askWeight(&weight);

    /* Negative weight <=> Leave the article.
    *  (Like not wanting it last minute) */
    if (weight <= 0.f)
        return NULL;

    return Tomato_init(weight);
}

/* ************************************************************************* */
char fillBasket(struct Basket *b)
{
    static int16_t userChoice = 0;
    static struct Article *article = NULL;
    static struct Article ** l_tmp = NULL;

    /* Check basket's existence */
    if ( !b ) {
        printf("You didn't take a basket!\n");
        return 1;
    }

    userChoice = chooseArticle();

    if (userChoice == SHOPPING_STOPPED) {
        return 0;
    }

    switch (userChoice) {
    case SHOPPING_REPEAT:   return 1;

    case SHOPPING_BANANA:
        article = takeBanana();
        break;

    case SHOPPING_CHEESE:
        article = takeCheese();
        break;

    case SHOPPING_DRINK:
        article = takeDrink();
        break;
    
    case SHOPPING_MEAT:
        article = takeMeat();
        break;
    
    case SHOPPING_PEPPER:
        article = takePepper();
        break;
    
    case SHOPPING_TOMATO:
        article = takeTomato();
        break;
        
    default:
        printf("Wanted article is not implemented yet or not sold.\n");
        return 1;
    }

    if ( ! article ) {
        /* If {Article}_init fails, shopping continues,
         * but tell the user the shop might be over-crownded.
         * (Analogy: No more space left to run
         *           '-> No more space between alley.) */
        printf("%s_init failed: The shop might be over-crowded.\n",
               articleTypes[userChoice]);
        return 1;
    }

    /* If current list is full, try reallocate with double the capacity. */
    if (b->size == b->capacity) {
        /* IMPORTANT: You need the temporary pointer! 
         *            In failure case, if you use directly the src,
         *            you will lose the current list and 
         *            will not be able to freed them! */
        l_tmp = (struct Article **)
                realloc(b->list, sizeof(struct Article *) * 2*b->capacity);

        if ( ! l_tmp ) {
            /* If realloc fails, shopping continues,
             * but tell the user to go checkout.
             * (Analogy: No more space in memory
             *           '-> No more space in basket.) */
            printf("realloc failed: Articles can't be added anymore,\n"
                   "                might want to checkout.\n");
            return 1;
        }

        /* Update "members" */
        b->capacity *= 2;
        b->list = l_tmp;
    }

    /* Add article and increase size */
    b->list[b->size++] = article;

    return 1;
}
