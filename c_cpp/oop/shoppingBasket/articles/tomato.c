
#include "tomato.h" /* Associated header */

/* Standard libraries */
#include <stdlib.h>
#include <string.h>

/* Custom modules */
#include "article.h"
#include "../utils/random_bool.h"

/* Tomato's functions table initialization */
struct TomatoFuncTable {
	struct ArticleFuncTable super;
    /* Eventually "class" dedicated function(s) */
    /* ... */
} tomatoFuncTable = {
	{
		.getName            = Tomato_getName,
		.getUnitPrice       = Tomato_getUnitPrice,
        .getWeight          = Tomato_getWeight,
        .getQuantity        = NULL,
        .getTotalPrice      = Tomato_getTotalPrice,
        .getDiscountStatus  = Tomato_getDiscountStatus,

		.destructor_        = Tomato_destroy
	},
};

/* *** Constructor/Destructor ********* */
/* ************************************************************************* */
struct Article* Tomato_init(float weightKg)
{
	struct Tomato *obj = (struct Tomato *) malloc(sizeof(struct Tomato));

    /* Check on memory allocation and weight arg. */
    if ( !obj || weightKg <= 0.f) {
        return NULL;
    }

    /* Associate functions table to "object" */
	obj->super.funcTable = (struct ArticleFuncTable *) &tomatoFuncTable;

    /* Initialize every "members" */
    strncpy(obj->name, TOMATO_NAME, sizeof(TOMATO_NAME));
	obj->unitPriceKg = TOMATO_UNIT_PRICE;
	obj->weightKg    = weightKg;
	obj->totalPrice  = TOMATO_UNIT_PRICE * weightKg;
    obj->hasDiscount = rand_bool(4);
    if (obj->hasDiscount) { /* Apply discount if there is some */
        obj->totalPrice *= (1.f - TOMATO_DISCOUNT);
    }

	return (struct Article *) obj;
}

/* ************************************************************************* */
void Tomato_destroy(struct Article *obj)
{
	Article_destroy(obj);
	free(obj);
}

/* *** Accessors : Getters ********* */
/* ************************************************************************* */
char * Tomato_getName(struct Article * obj)
{
    return ((struct Tomato *)obj)->name;
}

/* ************************************************************************* */
float Tomato_getUnitPrice(struct Article * obj)
{
    return ((struct Tomato *)obj)->unitPriceKg;
}

/* ************************************************************************* */
float Tomato_getWeight(struct Article * obj)
{
    return ((struct Tomato *)obj)->weightKg;
}

/* ************************************************************************* */
float Tomato_getTotalPrice(struct Article * obj)
{
    return ((struct Tomato *)obj)->totalPrice;
}

/* ************************************************************************* */
char Tomato_getDiscountStatus(struct Article * obj)
{
    return ((struct Tomato *)obj)->hasDiscount;
}

/* *** Accessors : Setters ********* */
/* ... */