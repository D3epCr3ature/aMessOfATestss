
#include "pepper.h" /* Associated header */

/* Standard libraries */
#include <stdlib.h>
#include <string.h>

/* Custom modules */
#include "article.h"
#include "../utils/random_bool.h"

/* Pepper's functions table initialization */
struct PepperFuncTable {
	struct ArticleFuncTable super;
    /* Eventually "class" dedicated function(s) */
    /* ... */
} pepperFuncTable = {
	{
		.getName            = Pepper_getName,
		.getUnitPrice       = Pepper_getUnitPrice,
        .getWeight          = Pepper_getWeight,
        .getQuantity        = NULL,
        .getTotalPrice      = Pepper_getTotalPrice,
        .getDiscountStatus  = Pepper_getDiscountStatus,

		.destructor_        = Pepper_destroy
	},
};

/* *** Constructor/Destructor ********* */
/* ************************************************************************* */
struct Article* Pepper_init(float weightKg)
{
	struct Pepper *obj = (struct Pepper *) malloc(sizeof(struct Pepper));

    /* Check on memory allocation and weight arg. */
    if ( !obj || weightKg <= 0.f) {
        return NULL;
    }

    /* Associate functions table to "object" */
	obj->super.funcTable = (struct ArticleFuncTable *) &pepperFuncTable;

    /* Initialize every "members" */
    strncpy(obj->name, PEPPER_NAME, sizeof(PEPPER_NAME));
	obj->unitPriceKg = PEPPER_UNIT_PRICE;
	obj->weightKg    = weightKg;
	obj->totalPrice  = PEPPER_UNIT_PRICE * weightKg;
    obj->hasDiscount = rand_bool(5);
    if (obj->hasDiscount) { /* Apply discount if there is some */
        obj->totalPrice *= (1.f - PEPPER_DISCOUNT);
    }

	return (struct Article *) obj;
}

/* ************************************************************************* */
void Pepper_destroy(struct Article *obj)
{
	Article_destroy(obj);
	free(obj);
}

/* *** Accessors : Getters ********* */
/* ************************************************************************* */
char * Pepper_getName(struct Article * obj)
{
    return ((struct Pepper *)obj)->name;
}

/* ************************************************************************* */
float Pepper_getUnitPrice(struct Article * obj)
{
    return ((struct Pepper *)obj)->unitPriceKg;
}

/* ************************************************************************* */
float Pepper_getWeight(struct Article * obj)
{
    return ((struct Pepper *)obj)->weightKg;
}

/* ************************************************************************* */
float Pepper_getTotalPrice(struct Article * obj)
{
    return ((struct Pepper *)obj)->totalPrice;
}

/* ************************************************************************* */
char Pepper_getDiscountStatus(struct Article * obj)
{
    return ((struct Pepper *)obj)->hasDiscount;
}

/* *** Accessors : Setters ********* */
/* ... */