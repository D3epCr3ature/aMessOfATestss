
#include "meat.h"   /* Associated header */

/* Standard libraries */
#include <stdlib.h>
#include <string.h>

/* Custom modules */
#include "article.h"
#include "../utils/random_bool.h"

/* Meat's functions table initialization */
struct MeatFuncTable {
	struct ArticleFuncTable super;
    /* Eventually "class" dedicated function(s) */
    /* ... */
} meatFuncTable = {
	{
		.getName            = Meat_getName,
		.getUnitPrice       = Meat_getUnitPrice,
        .getWeight          = Meat_getWeight,
        .getQuantity        = NULL,
        .getTotalPrice      = Meat_getTotalPrice,
        .getDiscountStatus  = Meat_getDiscountStatus,

		.destructor_        = Meat_destroy
	},
};

/* *** Constructor/Destructor ********* */
/* ************************************************************************* */
struct Article* Meat_init(const char *name, float weightKg)
{
    static int nameLen = 0;
    static const char *_name = NULL;

	struct Meat *obj = (struct Meat *) malloc(sizeof(struct Meat));

    /* Check on memory allocation and weight arg. */
    if ( !obj || weightKg <= 0.f) {
        return NULL;
    }

    /* Check on name's existence OR empty name */
    if ( !name || *name == '\0' ) {
        _name = MEAT_DEFAULT_NAME;
    } else {
        _name = name;
    }

    /* Associate functions table to "object" */
	obj->super.funcTable = (struct ArticleFuncTable *) &meatFuncTable;

    /* Initialize every "members" */
    /* Set name properly, regarding name length */
    nameLen = strlen(_name);
    if (nameLen < MEAT_NAME_LENGTH) {
        strncpy(obj->name, _name, nameLen);
        /* Properly set remaining space to '\0' */
        memset(obj->name+nameLen, 0, MEAT_NAME_LENGTH - nameLen);
    } else {
        strncpy(obj->name, _name, MEAT_NAME_LENGTH);
    }
    obj->name[MEAT_NAME_LENGTH] = '\0';
	obj->unitPriceKg = MEAT_UNIT_PRICE;
	obj->weightKg    = weightKg;
	obj->totalPrice  = MEAT_UNIT_PRICE * weightKg;
    obj->hasDiscount = rand_bool(2);
    if (obj->hasDiscount) { /* Apply discount if there is some */
        obj->totalPrice *= (1.f - MEAT_DISCOUNT);
    }

	return (struct Article *) obj;
}

/* ************************************************************************* */
void Meat_destroy(struct Article *obj)
{
	Article_destroy(obj);
	free(obj);
}

/* *** Accessors : Getters ********* */
/* ************************************************************************* */
char * Meat_getName(struct Article * obj)
{
    return ((struct Meat *)obj)->name;
}

/* ************************************************************************* */
float Meat_getUnitPrice(struct Article * obj)
{
    return ((struct Meat *)obj)->unitPriceKg;
}

/* ************************************************************************* */
float Meat_getWeight(struct Article * obj)
{
    return ((struct Meat *)obj)->weightKg;
}

/* ************************************************************************* */
float Meat_getTotalPrice(struct Article * obj)
{
    return ((struct Meat *)obj)->totalPrice;
}

/* ************************************************************************* */
char Meat_getDiscountStatus(struct Article * obj)
{
    return ((struct Meat *)obj)->hasDiscount;
}

/* *** Accessors : Setters ********* */
/* ... */