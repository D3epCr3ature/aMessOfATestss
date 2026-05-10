/** 
 * @file drink.h
 * 
 * @brief "Sub-Class" of a Drink that uses the "super class" article.
 */
#ifndef __DRINK_H__
#define __DRINK_H__

#include "article.h"

/*****************************************************************************
 * @def DRINK_NAME_LENGTH
 * @brief Represent the "class"'s base name length.
 * 
 * @note When declaring an name array with it, don't forget the "+1" for '\0'.
 *****************************************************************************/
#define DRINK_NAME_LENGTH   20

/*****************************************************************************
 * @def DRINK_DEFAULT_NAME
 * @brief Represent the "class"'s default name.
 * 
 * @note sizeof a string take '\0' in consideration
 *****************************************************************************/
#define DRINK_DEFAULT_NAME  "Drink's variant"

/*****************************************************************************
 * @def DRINK_UNIT_PRICE
 * @brief Represent the "class"'s base unit price per unit.
 *****************************************************************************/
#define DRINK_UNIT_PRICE    0.60f

/*****************************************************************************
 * @def DRINK_DISCOUNT
 * @brief Represent the "class"'s base discount percent per unit.
 *****************************************************************************/
#define DRINK_DISCOUNT      0.05f

/*****************************************************************************
 * @struct Drink
 * @brief Represent the "class" of a drink article.
 * 
 * @var Drink::super Represent the "super class" access
 * @var Drink::name  Represent the "class" name
 * @var Drink::unitPriceKg Represent the "class" unit price [CHF/Qty]
 * @var Drink::weightKg    Represent the "class" quanity
 * @var Drink::totalPrice  Represent the "class" total price in [CHF]
 * @var Drink::hasDiscount Represent the "class" discount status
 *****************************************************************************/
struct Drink {
	struct Article super;

    char  name[DRINK_NAME_LENGTH+1];    /* +1 for '\0' */
    float unitPriceKg;                  /* Unit price [CHF/Qty] */
    unsigned int quantity;              /* Quantity [#] */
    float totalPrice;                   /* Unit price * quantity */
    char  hasDiscount;
};

/* *** Constructor/Destructor ********* */
/*****************************************************************************
 * @brief "Class" drink constructor
 * @param name     Name of the drink.
 * @param quantity Weight of the drink in [kg].
 * @return Pointer to newly allocated element
 *****************************************************************************/
struct Article* Drink_init(const char *name, unsigned int quantity);

/*****************************************************************************
 * @brief "Class" drink destructor
 * @param obj Pointed "class object" to free memory from.
 *****************************************************************************/
void   Drink_destroy(struct Article* obj);

/* *** Accessors : Getters ********* */
/*****************************************************************************
 * @brief Drink's name getter
 * @param obj Pointed "class object"
 * @return Drink's name array address
 *****************************************************************************/
char *       Drink_getName(struct Article * obj);

/*****************************************************************************
 * @brief Drink's unit price getter
 * @param obj Pointed "class object"
 * @return Drink's unit price
 *****************************************************************************/
float        Drink_getUnitPrice(struct Article * obj);

/*****************************************************************************
 * @brief Drink's quantity getter
 * @param obj Pointed "class object"
 * @return Drink's quantity
 *****************************************************************************/
unsigned int Drink_getQuantity(struct Article * obj);

/*****************************************************************************
 * @brief Drink's total price getter
 * @param obj Pointed "class object"
 * @return Drink's total price
 *****************************************************************************/
float        Drink_getTotalPrice(struct Article * obj);

/*****************************************************************************
 * @brief Drink's discount status getter
 * @param obj Pointed "class object"
 * @return Drink's discount status
 * 
 * @note The discount status is returned through a char,
 *       but only the least significant bit is used.
 *****************************************************************************/
char         Drink_getDiscountStatus(struct Article * obj);

/* *** Accessors : Setters ********* */
/* ... */

#endif /* __DRINK_H__ */