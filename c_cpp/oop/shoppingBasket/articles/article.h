/** 
 * @file article.h
 * 
 * @brief "Super class" for an article, based on the OOP paradigm in C.
 * 
 * For a shopping basket project, this file offers a "super class" of article.
 * The project mostly uses getters, but the structure is prepared to receive
 * setters if you want.
 */
#ifndef __ARTICLE_H__
#define __ARTICLE_H__

#include <assert.h>

/* TODO: enum for type identification ? */

/* Pre-declaration to use a pointer on it in the article structure */
struct ArticleFuncTable;

/*****************************************************************************
 * @struct Article
 * @brief Represent the "super class" of any article.
 * 
 * @var Article::funcTable Is the group of generic functions shared
 *                         among articles (see struct ArticleFuncTable)
 *****************************************************************************/
struct Article {
        struct ArticleFuncTable *funcTable;
        /* TODO: Group common "members, like fns ? */
};

/*****************************************************************************
 * @struct ArticleFuncTable
 * @brief Represent the group of generic functions shared among articles.
 * 
 * @var ArticleFuncTable::getName           Generic getter for article's name
 * @var ArticleFuncTable::getUnitPrice      .. for article's unit price
 * @var ArticleFuncTable::getWeight         .. for article's weight
 * @var ArticleFuncTable::getQuantity       .. for article's quantity
 * @var ArticleFuncTable::getTotalPrice     .. for article's total price
 *                                          ([weight|quantity] * unit price)
 * @var ArticleFuncTable::getDiscountStatus .. for article's discount state)
 * @var ArticleFuncTable::destroy_          .. for article's destructor
 *
 * @note Depending on the article, set either getWeight or getQuantity
 *       and set NULL to the other.
 * @example For bananas, you'll mostly weight them before going to the casier.
 *          Whereas for drinks, it's about the amount of bottles you take.
 *****************************************************************************/
struct ArticleFuncTable {
        /* Accessors : Getters */
        char*        (* getName       ) ( struct Article* obj );
        float        (* getUnitPrice  ) ( struct Article* obj );
        float        (* getWeight     ) ( struct Article* obj );
        unsigned int (* getQuantity   ) ( struct Article* obj );
        float        (* getTotalPrice ) ( struct Article* obj );
        char         (* getDiscountStatus ) ( struct Article* obj );

        /* Accessors : Setters */
        /* ... */

        /* Destructor */
        void         (* destructor_   ) ( struct Article* obj );
};

/* *** Constructor/Destructor ********* */
/*****************************************************************************
 * @brief "Super class" constructor
 * 
 * @note As each article will mostly have different arguments for 
 *       their constructor, this function is here for principle purpose.
 *       As you can see in the body, it has an assert(0) that implies that
 *       it should not be used.
 *****************************************************************************/
struct Article* Article_init(void);

/*****************************************************************************
 * @brief "Super class" destructor
 *****************************************************************************/
void   Article_destroy (struct Article* obj );

/* *** Accessors : Getters ********* */
/*****************************************************************************
 * @def Article_GETNAME
 * @brief Macro to call the getName function of any article.
 * 
 * Macro that cast the "child object" into the "super class" to call
 * the generic getName function.
 *****************************************************************************/
#define Article_GETNAME( obj ) \
        (( struct Article *) ( obj ))->funcTable->getName((obj))

/*****************************************************************************
 * @def Article_GETUNITPRICE
 * @brief Macro to call the getUnitPrice function of any article.
 * 
 * Macro that cast the "child object" into the "super class" to call
 * the generic getUnitPrice function.
 *****************************************************************************/
#define Article_GETUNITPRICE( obj ) \
        (( struct Article *) ( obj ))->funcTable->getUnitPrice((obj))

/*****************************************************************************
 * @def Article_GETWEIGHT
 * @brief Macro to call the getWeight function of any article.
 * 
 * Macro that cast the "child object" into the "super class" to call
 * the generic getWeight function.
 *****************************************************************************/
#define Article_GETWEIGHT( obj ) \
        (( struct Article *) ( obj ))->funcTable->getWeight((obj))

/*****************************************************************************
 * @def Article_GETQUANTITY
 * @brief Macro to call the getQuantity function of any article.
 * 
 * Macro that cast the "child object" into the "super class" to call
 * the generic getQuantity function.
 *****************************************************************************/
#define Article_GETQUANTITY( obj ) \
        (( struct Article *) ( obj ))->funcTable->getQuantity((obj))

/*****************************************************************************
 * @def Article_GETTOTALPRICE
 * @brief Macro to call the getTotalPrice function of any article.
 * 
 * Macro that cast the "child object" into the "super class" to call
 * the generic getTotalPrice function.
 *****************************************************************************/
#define Article_GETTOTALPRICE( obj ) \
        (( struct Article *) ( obj ))->funcTable->getTotalPrice((obj))

/*****************************************************************************
 * @def Article_GETDISCOUNTSTATUS
 * @brief Macro to call the getDiscountStatus function of any article.
 * 
 * Macro that cast the "child object" into the "super class" to call
 * the generic getDiscountStatus function.
 *****************************************************************************/
#define Article_GETDISCOUNTSTATUS( obj ) \
        (( struct Article *) ( obj ))->funcTable->getDiscountStatus((obj))

/*****************************************************************************
 * @def Article_DESTROY
 * @brief Macro to call the destructor function of any article.
 * 
 * Macro that cast the "child object" into the "super class" to call
 * the generic destructor function.
 *****************************************************************************/
#define Article_DESTROY( obj ) \
        (( struct Article *) ( obj ))->funcTable->destructor_((obj))

/* *** Accessors : Setters ********* */
/* ... */

#endif /* __ARTICLE_H__ */