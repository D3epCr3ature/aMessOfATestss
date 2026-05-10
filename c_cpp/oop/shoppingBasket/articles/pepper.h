/** 
 * @file pepper.h
 * 
 * @brief "Sub-Class" of a Pepper that uses the "super class" article.
 */
#ifndef __PEPPER_H__
#define __PEPPER_H__

#include "article.h"

/*****************************************************************************
 * @def PEPPER_NAME
 * @brief Represent the "class"'s base name.
 * 
 * @note sizeof a string take '\0' in consideration
 *****************************************************************************/
#define PEPPER_NAME         "Pepper"

/*****************************************************************************
 * @def PEPPER_UNIT_PRICE
 * @brief Represent the "class"'s base unit price for 1[kg] in [CHF].
 *****************************************************************************/
#define PEPPER_UNIT_PRICE   0.72f

/*****************************************************************************
 * @def PEPPER_DISCOUNT
 * @brief Represent the "class"'s base discount percent by 1[kg].
 *****************************************************************************/
#define PEPPER_DISCOUNT     0.08f

/*****************************************************************************
 * @struct Pepper
 * @brief Represent the "class" of a pepper article.
 * 
 * @var Pepper::super Represent the "super class" access
 * @var Pepper::name  Represent the "class" name
 * @var Pepper::unitPriceKg Represent the "class" unit price [CHF/kg]
 * @var Pepper::weightKg    Represent the "class" weight in [kg]
 * @var Pepper::totalPrice  Represent the "class" total price in [CHF]
 * @var Pepper::hasDiscount Represent the "class" discount status
 *****************************************************************************/
struct Pepper {
	struct Article super;

    char  name[sizeof(PEPPER_NAME)];
    float unitPriceKg;  /* Unit price [CHF/kg] */
    float weightKg;     /* Weight [kg] */
    float totalPrice;   /* Unit price * weight */
    char  hasDiscount;
};

/* *** Constructor/Destructor ********* */
/*****************************************************************************
 * @brief "Class" pepper constructor
 * @param weightKg Weight of pepper(s) in [kg].
 * @return Pointer to newly allocated element
 *****************************************************************************/
struct Article* Pepper_init(float weightKg);

/*****************************************************************************
 * @brief "Class" pepper destructor
 * @param obj Pointed "class object" to free memory from.
 *****************************************************************************/
void   Pepper_destroy(struct Article* obj);

/* *** Accessors : Getters ********* */
/*****************************************************************************
 * @brief Pepper's name getter
 * @param obj Pointed "class object"
 * @return Pepper's name array address
 *****************************************************************************/
char * Pepper_getName(struct Article * obj);

/*****************************************************************************
 * @brief Pepper's unit price getter
 * @param obj Pointed "class object"
 * @return Pepper's unit price
 *****************************************************************************/
float  Pepper_getUnitPrice(struct Article * obj);

/*****************************************************************************
 * @brief Pepper's weight getter
 * @param obj Pointed "class object"
 * @return Pepper's weight
 *****************************************************************************/
float  Pepper_getWeight(struct Article * obj);

/*****************************************************************************
 * @brief Pepper's total price getter
 * @param obj Pointed "class object"
 * @return Pepper's total price
 *****************************************************************************/
float  Pepper_getTotalPrice(struct Article * obj);

/*****************************************************************************
 * @brief Pepper's discount status getter
 * @param obj Pointed "class object"
 * @return Pepper's discount status
 * 
 * @note The discount status is returned through a char,
 *       but only the least significant bit is used.
 *****************************************************************************/
char   Pepper_getDiscountStatus(struct Article * obj);

/* *** Accessors : Setters ********* */
/* ... */

#endif /* __PEPPER_H__ */