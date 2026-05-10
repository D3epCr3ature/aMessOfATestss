/** 
 * @file cheese.h
 * 
 * @brief "Sub-Class" of a Cheese that uses the "super class" article.
 */
#ifndef __CHEESE_H__
#define __CHEESE_H__

#include "article.h"

/*****************************************************************************
 * @def CHEESE_NAME_LENGTH
 * @brief Represent the "class"'s base name length.
 * 
 * @note When declaring an name array with it, don't forget the "+1" for '\0'.
 *****************************************************************************/
#define CHEESE_NAME_LENGTH  20

/*****************************************************************************
 * @def CHEESE_DEFAULT_NAME
 * @brief Represent the "class"'s default name.
 * 
 * @note sizeof a string take '\0' in consideration
 *****************************************************************************/
#define CHEESE_DEFAULT_NAME "Cheese's variant"

/*****************************************************************************
 * @def CHEESE_UNIT_PRICE
 * @brief Represent the "class"'s base unit price for 1[kg] in [CHF].
 *****************************************************************************/
#define CHEESE_UNIT_PRICE   1.75f

/*****************************************************************************
 * @def CHEESE_DISCOUNT
 * @brief Represent the "class"'s base discount percent by 1[kg].
 *****************************************************************************/
#define CHEESE_DISCOUNT     0.17f

/*****************************************************************************
 * @struct Cheese
 * @brief Represent the "class" of a cheese article.
 * 
 * @var Cheese::super Represent the "super class" access
 * @var Cheese::name  Represent the "class" name
 * @var Cheese::unitPriceKg Represent the "class" unit price [CHF/kg]
 * @var Cheese::weightKg    Represent the "class" weight in [kg]
 * @var Cheese::totalPrice  Represent the "class" total price in [CHF]
 * @var Cheese::hasDiscount Represent the "class" discount status
 *****************************************************************************/
struct Cheese {
	struct Article super;

    char  name[CHEESE_NAME_LENGTH+1];   /* +1 for '\0' */
    float unitPriceKg;                  /* Unit price [CHF/kg] */
    float weightKg;                     /* Weight [kg] */
    float totalPrice;                   /* Unit price * weight */
    char  hasDiscount;
};

/* *** Constructor/Destructor ********* */
/*****************************************************************************
 * @brief "Class" cheese constructor
 * @param name     Name of the cheese.
 * @param weightKg Weight of the cheese in [kg].
 * @return Pointer to newly allocated element
 *****************************************************************************/
struct Article* Cheese_init(const char *name, float weightKg);

/*****************************************************************************
 * @brief "Class" cheese destructor
 * @param obj Pointed "class object" to free memory from.
 *****************************************************************************/
void   Cheese_destroy(struct Article* obj);

/* *** Accessors : Getters ********* */
/*****************************************************************************
 * @brief Cheese's name getter
 * @param obj Pointed "class object"
 * @return Cheese's name array address
 *****************************************************************************/
char * Cheese_getName(struct Article * obj);

/*****************************************************************************
 * @brief Cheese's unit price getter
 * @param obj Pointed "class object"
 * @return Cheese's unit price
 *****************************************************************************/
float  Cheese_getUnitPrice(struct Article * obj);

/*****************************************************************************
 * @brief Cheese's weight getter
 * @param obj Pointed "class object"
 * @return Cheese's weight
 *****************************************************************************/
float  Cheese_getWeight(struct Article * obj);

/*****************************************************************************
 * @brief Cheese's total price getter
 * @param obj Pointed "class object"
 * @return Cheese's total price
 *****************************************************************************/
float  Cheese_getTotalPrice(struct Article * obj);

/*****************************************************************************
 * @brief Cheese's discount status getter
 * @param obj Pointed "class object"
 * @return Cheese's discount status
 * 
 * @note The discount status is returned through a char,
 *       but only the least significant bit is used.
 *****************************************************************************/
char   Cheese_getDiscountStatus(struct Article * obj);

/* *** Accessors : Setters ********* */
/* ... */

#endif /* __CHEESE_H__ */