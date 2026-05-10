
#include "cheese.h" /* Associated header */

/* Standard libraries */
#include <stdlib.h>
#include <string.h>

/* Custom modules */
#include "article.h"
#include "../utils/random_bool.h"

/* Cheese's functions table initialization */
struct CheeseFuncTable {
	struct ArticleFuncTable super;
    /* Eventually "class" dedicated function(s) */
    /* ... */
} cheeseFuncTable = {
	{
		.getName            = Cheese_getName,
		.getUnitPrice       = Cheese_getUnitPrice,
        .getWeight          = Cheese_getWeight,
        .getQuantity        = NULL,
        .getTotalPrice      = Cheese_getTotalPrice,
        .getDiscountStatus  = Cheese_getDiscountStatus,

		.destructor_        = Cheese_destroy
	},
};

/* *** Constructor/Destructor ********* */
/* ************************************************************************* */
struct Article* Cheese_init(const char *name, float weightKg)
{
    static int nameLen = 0;
    static const char *_name = NULL;

	struct Cheese *obj = (struct Cheese *) malloc(sizeof(struct Cheese));
    
    /* Check on memory allocation and weight arg. */
    if ( !obj || weightKg <= 0.f) {
        return NULL;
    }

    /* Check on name's existence OR empty name */
    if ( !name || *name == '\0' ) {
        _name = CHEESE_DEFAULT_NAME;
    } else {
        _name = name;
    }

    /* Associate functions table to "object" */
	obj->super.funcTable = (struct ArticleFuncTable *) &cheeseFuncTable;

    /* Initialize every "members" */
    /* Set name properly, regarding name length */
    nameLen = strlen(_name);
    if (nameLen < CHEESE_NAME_LENGTH) {
        strncpy(obj->name, _name, nameLen);
        /* Properly set remaining space to '\0' */
        memset(obj->name+nameLen, 0, CHEESE_NAME_LENGTH - nameLen);
    } else {
        strncpy(obj->name, _name, CHEESE_NAME_LENGTH);
    }
    obj->name[CHEESE_NAME_LENGTH] = '\0';
	obj->unitPriceKg = CHEESE_UNIT_PRICE;
	obj->weightKg    = weightKg;
	obj->totalPrice  = CHEESE_UNIT_PRICE * weightKg;
    obj->hasDiscount = rand_bool(1);
    if (obj->hasDiscount) { /* Apply discount if there is some */
        obj->totalPrice *= (1.f - CHEESE_DISCOUNT);
    }

	return (struct Article *) obj;
}

/* ************************************************************************* */
void Cheese_destroy(struct Article *obj)
{
	Article_destroy(obj);
	free(obj);
}

/* *** Accessors : Getters ********* */
/* ************************************************************************* */
char * Cheese_getName(struct Article * obj)
{
    return ((struct Cheese *)obj)->name;
}

/* ************************************************************************* */
float Cheese_getUnitPrice(struct Article * obj)
{
    return ((struct Cheese *)obj)->unitPriceKg;
}

/* ************************************************************************* */
float Cheese_getWeight(struct Article * obj)
{
    return ((struct Cheese *)obj)->weightKg;
}

/* ************************************************************************* */
float Cheese_getTotalPrice(struct Article * obj)
{
    return ((struct Cheese *)obj)->totalPrice;
}

/* ************************************************************************* */
char Cheese_getDiscountStatus(struct Article * obj)
{
    return ((struct Cheese *)obj)->hasDiscount;
}

/* *** Accessors : Setters ********* */
/* ... */