/** 
 * @file meat.h
 * 
 * @brief "Sub-Class" of a Meat that uses the "super class" article.
 */
#ifndef __MEAT_H__
#define __MEAT_H__

#include "article.h"

/*****************************************************************************
 * @def MEAT_NAME_LENGTH
 * @brief Represent the "class"'s base name length.
 * 
 * @note When declaring an name array with it, don't forget the "+1" for '\0'.
 *****************************************************************************/
#define MEAT_NAME_LENGTH    20

/*****************************************************************************
 * @def MEAT_DEFAULT_NAME
 * @brief Represent the "class"'s default name.
 * 
 * @note sizeof a string take '\0' in consideration
 *****************************************************************************/
#define MEAT_DEFAULT_NAME   "Meat's variant"

/*****************************************************************************
 * @def MEAT_UNIT_PRICE
 * @brief Represent the "class"'s base unit price for 1[kg] in [CHF].
 *****************************************************************************/
#define MEAT_UNIT_PRICE     13.24f

/*****************************************************************************
 * @def MEAT_DISCOUNT
 * @brief Represent the "class"'s base discount percent by 1[kg].
 *****************************************************************************/
#define MEAT_DISCOUNT       0.12f

/*****************************************************************************
 * @struct Meat
 * @brief Represent the "class" of a meat article.
 * 
 * @var Meat::super Represent the "super class" access
 * @var Meat::name  Represent the "class" name
 * @var Meat::unitPriceKg Represent the "class" unit price [CHF/kg]
 * @var Meat::weightKg    Represent the "class" weight in [kg]
 * @var Meat::totalPrice  Represent the "class" total price in [CHF]
 * @var Meat::hasDiscount Represent the "class" discount status
 *****************************************************************************/
struct Meat {
	struct Article super;

    char  name[MEAT_NAME_LENGTH+1]; /* +1 for '\0' */
    float unitPriceKg;              /* Unit price [CHF/kg] */
    float weightKg;                 /* Weight [kg] */
    float totalPrice;               /* Unit price * weight */
    char  hasDiscount;
};

/* *** Constructor/Destructor ********* */
/*****************************************************************************
 * @brief "Class" meat constructor
 * @param name     Name of the meat.
 * @param weightKg Weight of the meat in [kg].
 * @return Pointer to newly allocated element
 *****************************************************************************/
struct Article* Meat_init(const char *name, float weightKg);

/*****************************************************************************
 * @brief "Class" meat destructor
 * @param obj Pointed "class object" to free memory from.
 *****************************************************************************/
void   Meat_destroy(struct Article* obj);

/* *** Accessors : Getters ********* */
/*****************************************************************************
 * @brief Meat's name getter
 * @param obj Pointed "class object"
 * @return Meat's name array address
 *****************************************************************************/
char * Meat_getName(struct Article * obj);

/*****************************************************************************
 * @brief Meat's unit price getter
 * @param obj Pointed "class object"
 * @return Meat's unit price
 *****************************************************************************/
float  Meat_getUnitPrice(struct Article * obj);

/*****************************************************************************
 * @brief Meat's weight getter
 * @param obj Pointed "class object"
 * @return Meat's weight
 *****************************************************************************/
float  Meat_getWeight(struct Article * obj);

/*****************************************************************************
 * @brief Meat's total price getter
 * @param obj Pointed "class object"
 * @return Meat's total price
 *****************************************************************************/
float  Meat_getTotalPrice(struct Article * obj);

/*****************************************************************************
 * @brief Meat's discount status getter
 * @param obj Pointed "class object"
 * @return Meat's discount status
 * 
 * @note The discount status is returned through a char,
 *       but only the least significant bit is used.
 *****************************************************************************/
char   Meat_getDiscountStatus(struct Article * obj);

/* *** Accessors : Setters ********* */
/* ... */

#endif /* __MEAT_H__ */