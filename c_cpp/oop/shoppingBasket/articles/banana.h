/** 
 * @file banana.h
 * 
 * @brief "Sub-Class" of a Banana that uses the "super class" article.
 */
#ifndef __BANANA_H__
#define __BANANA_H__

#include "article.h"

/*****************************************************************************
 * @def BANANA_NAME
 * @brief Represent the "class"'s base name.
 * 
 * @note sizeof a string take '\0' in consideration
 *****************************************************************************/
#define BANANA_NAME         "Banana"

/*****************************************************************************
 * @def BANANA_UNIT_PRICE
 * @brief Represent the "class"'s base unit price for 1[kg] in [CHF].
 *****************************************************************************/
#define BANANA_UNIT_PRICE   1.05f

/*****************************************************************************
 * @def BANANA_DISCOUNT
 * @brief Represent the "class"'s base discount percent by 1[kg].
 *****************************************************************************/
#define BANANA_DISCOUNT     0.15f

/*****************************************************************************
 * @struct Banana
 * @brief Represent the "class" of a banana article.
 * 
 * @var Banana::super Represent the "super class" access
 * @var Banana::name  Represent the "class" name
 * @var Banana::unitPriceKg Represent the "class" unit price [CHF/kg]
 * @var Banana::weightKg    Represent the "class" weight in [kg]
 * @var Banana::totalPrice  Represent the "class" total price in [CHF]
 * @var Banana::hasDiscount Represent the "class" discount status
 *****************************************************************************/
struct Banana {
	struct Article super;

    char  name[sizeof(BANANA_NAME)];
    float unitPriceKg;  /* Unit price [CHF/kg] */
    float weightKg;     /* Weight [kg] */
    float totalPrice;   /* Unit price * weight */
    char  hasDiscount;
};

/* *** Constructor/Destructor ********* */
/*****************************************************************************
 * @brief "Class" banana constructor
 * @param weightKg Weight of banana(s) in [kg].
 * @return Pointer to newly allocated element
 *****************************************************************************/
struct Article* Banana_init(float weightKg);

/*****************************************************************************
 * @brief "Class" banana destructor
 * @param obj Pointed "class object" to free memory from.
 *****************************************************************************/
void   Banana_destroy(struct Article* obj);

/* *** Accessors : Getters ********* */
/*****************************************************************************
 * @brief Banana's name getter
 * @param obj Pointed "class object"
 * @return Banana's name array address
 *****************************************************************************/
char * Banana_getName(struct Article * obj);

/*****************************************************************************
 * @brief Banana's unit price getter
 * @param obj Pointed "class object"
 * @return Banana's unit price
 *****************************************************************************/
float  Banana_getUnitPrice(struct Article * obj);

/*****************************************************************************
 * @brief Banana's weight getter
 * @param obj Pointed "class object"
 * @return Banana's weight
 *****************************************************************************/
float  Banana_getWeight(struct Article * obj);

/*****************************************************************************
 * @brief Banana's total price getter
 * @param obj Pointed "class object"
 * @return Banana's total price
 *****************************************************************************/
float  Banana_getTotalPrice(struct Article * obj);

/*****************************************************************************
 * @brief Banana's discount status getter
 * @param obj Pointed "class object"
 * @return Banana's discount status
 * 
 * @note The discount status is returned through a char,
 *       but only the least significant bit is used.
 *****************************************************************************/
char   Banana_getDiscountStatus(struct Article * obj);

/* *** Accessors : Setters ********* */
/* ... */

#endif /* __BANANA_H__ */