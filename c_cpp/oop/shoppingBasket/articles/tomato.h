/** 
 * @file tomato.h
 * 
 * @brief "Sub-Class" of a Tomato that uses the "super class" article.
 */
#ifndef __TOMATO_H__
#define __TOMATO_H__

#include "article.h"

/*****************************************************************************
 * @def TOMATO_NAME
 * @brief Represent the "class"'s base name.
 * 
 * @note sizeof a string take '\0' in consideration
 *****************************************************************************/
#define TOMATO_NAME         "Tomato"

/*****************************************************************************
 * @def TOMATO_UNIT_PRICE
 * @brief Represent the "class"'s base unit price for 1[kg] in [CHF].
 *****************************************************************************/
#define TOMATO_UNIT_PRICE   0.97f

/*****************************************************************************
 * @def TOMATO_DISCOUNT
 * @brief Represent the "class"'s base discount percent by 1[kg].
 *****************************************************************************/
#define TOMATO_DISCOUNT     0.13f

/*****************************************************************************
 * @struct Tomato
 * @brief Represent the "class" of a Tomato article.
 * 
 * @var Tomato::super Represent the "super class" access
 * @var Tomato::name  Represent the "class" name
 * @var Tomato::unitPriceKg Represent the "class" unit price [CHF/kg]
 * @var Tomato::weightKg    Represent the "class" weight in [kg]
 * @var Tomato::totalPrice  Represent the "class" total price in [CHF]
 * @var Tomato::hasDiscount Represent the "class" discount status
 *****************************************************************************/
struct Tomato {
	struct Article super;

    char  name[sizeof(TOMATO_NAME)];
    float unitPriceKg;  /* Unit price [CHF/kg] */
    float weightKg;     /* Weight [kg] */
    float totalPrice;   /* Unit price * weight */
    char  hasDiscount;
};

/* *** Constructor/Destructor ********* */
/*****************************************************************************
 * @brief "Class" tomato constructor
 * @param weightKg Weight of tomato(s) in [kg].
 * @return Pointer to newly allocated element
 *****************************************************************************/
struct Article* Tomato_init(float weightKg);

/*****************************************************************************
 * @brief "Class" tomato destructor
 * @param obj Pointed "class object" to free memory from.
 *****************************************************************************/
void   Tomato_destroy(struct Article* obj);

/* *** Accessors : Getters ********* */
/*****************************************************************************
 * @brief Tomato's name getter
 * @param obj Pointed "class object"
 * @return Tomato's name array address
 *****************************************************************************/
char * Tomato_getName(struct Article * obj);

/*****************************************************************************
 * @brief Tomato's unit price getter
 * @param obj Pointed "class object"
 * @return Tomato's unit price
 *****************************************************************************/
float  Tomato_getUnitPrice(struct Article * obj);

/*****************************************************************************
 * @brief Tomato's weight getter
 * @param obj Pointed "class object"
 * @return Tomato's weight
 *****************************************************************************/
float  Tomato_getWeight(struct Article * obj);

/*****************************************************************************
 * @brief Tomato's total price getter
 * @param obj Pointed "class object"
 * @return Tomato's total price
 *****************************************************************************/
float  Tomato_getTotalPrice(struct Article * obj);

/*****************************************************************************
 * @brief Tomato's discount status getter
 * @param obj Pointed "class object"
 * @return Tomato's discount status
 * 
 * @note The discount status is returned through a char,
 *       but only the least significant bit is used.
 *****************************************************************************/
char   Tomato_getDiscountStatus(struct Article * obj);

/* *** Accessors : Setters ********* */
/* ... */

#endif /* __TOMATO_H__ */