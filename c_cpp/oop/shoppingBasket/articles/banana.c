
#include "banana.h" /* Associated header */

/* Standard libraries */
#include <stdlib.h>
#include <string.h>

/* Custom modules */
#include "article.h"
#include "../utils/random_bool.h"

/* Banana's functions table initialization */
struct BananaFuncTable {
	struct ArticleFuncTable super;
    /* Eventually "class" dedicated function(s) */
    /* ... */
} bananaFuncTable = {
	{
		.getName            = Banana_getName,
		.getUnitPrice       = Banana_getUnitPrice,
        .getWeight          = Banana_getWeight,
        .getQuantity        = NULL,
        .getTotalPrice      = Banana_getTotalPrice,
        .getDiscountStatus  = Banana_getDiscountStatus,

		.destructor_        = Banana_destroy
	},
};

/* *** Constructor/Destructor ********* */
/* ************************************************************************* */
struct Article* Banana_init(float weightKg)
{
	struct Banana *obj = (struct Banana *) malloc(sizeof(struct Banana));

    /* Check on memory allocation and weight arg. */
    if ( !obj || weightKg <= 0.f) {
        return NULL;
    }

    /* Associate functions table to "object" */
	obj->super.funcTable = (struct ArticleFuncTable *) &bananaFuncTable;

    /* Initialize every "members" */
    strncpy(obj->name, BANANA_NAME, sizeof(BANANA_NAME));
	obj->unitPriceKg = BANANA_UNIT_PRICE;
	obj->weightKg    = weightKg;
	obj->totalPrice  = BANANA_UNIT_PRICE * weightKg;
    obj->hasDiscount = rand_bool(3);
    if (obj->hasDiscount) { /* Apply discount if there is some */
        obj->totalPrice *= (1.f - BANANA_DISCOUNT);
    }

	return (struct Article *) obj;
}

/* ************************************************************************* */
void Banana_destroy(struct Article *obj)
{
	Article_destroy(obj);
	free(obj);
}

/* *** Accessors : Getters ********* */
/* ************************************************************************* */
char * Banana_getName(struct Article * obj)
{
    return ((struct Banana *)obj)->name;
}

/* ************************************************************************* */
float Banana_getUnitPrice(struct Article * obj)
{
    return ((struct Banana *)obj)->unitPriceKg;
}

/* ************************************************************************* */
float Banana_getWeight(struct Article * obj)
{
    return ((struct Banana *)obj)->weightKg;
}

/* ************************************************************************* */
float Banana_getTotalPrice(struct Article * obj)
{
    return ((struct Banana *)obj)->totalPrice;
}

/* ************************************************************************* */
char Banana_getDiscountStatus(struct Article * obj)
{
    return ((struct Banana *)obj)->hasDiscount;
}

/* *** Accessors : Setters ********* */
/* ... */