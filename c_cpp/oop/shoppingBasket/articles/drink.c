
#include "drink.h"  /* Associated header */

/* Standard libraries */
#include <stdlib.h>
#include <string.h>

/* Custom modules */
#include "article.h"
#include "../utils/random_bool.h"

/* Drink's functions table initialization */
struct DrinkFuncTable {
	struct ArticleFuncTable super;
    /* Eventually "class" dedicated function(s) */
    /* ... */
} drinkFuncTable = {
	{
		.getName            = Drink_getName,
		.getUnitPrice       = Drink_getUnitPrice,
        .getWeight          = NULL,
        .getQuantity        = Drink_getQuantity,
        .getTotalPrice      = Drink_getTotalPrice,
        .getDiscountStatus  = Drink_getDiscountStatus,

		.destructor_        = Drink_destroy
	},
};

/* *** Constructor/Destructor ********* */
/* ************************************************************************* */
struct Article* Drink_init(const char *name, unsigned int quantity)
{
    static int nameLen = 0;
    static const char *_name = NULL;

	struct Drink *obj = (struct Drink *) malloc(sizeof(struct Drink));
    
    /* Check on memory allocation and quantity arg. */
    if ( !obj || quantity == 0) {
        return NULL;
    }

    /* Check on name's existence OR empty name */
    if ( !name || *name == '\0' ) {
        _name = DRINK_DEFAULT_NAME;
    } else {
        _name = name;
    }

    /* Associate functions table to "object" */
	obj->super.funcTable = (struct ArticleFuncTable *) &drinkFuncTable;

    /* Initialize every "members" */
    /* Set name properly, regarding name length */
    nameLen = strlen(_name);
    if (nameLen < DRINK_NAME_LENGTH) {
        strncpy(obj->name, _name, nameLen);
        /* Properly set remaining space to '\0' */
        memset(obj->name+nameLen, 0, DRINK_NAME_LENGTH - nameLen);
    } else {
        strncpy(obj->name, _name, DRINK_NAME_LENGTH);
    }
    obj->name[DRINK_NAME_LENGTH] = '\0';
	obj->unitPriceKg = DRINK_UNIT_PRICE;
	obj->quantity    = quantity;
	obj->totalPrice  = DRINK_UNIT_PRICE * quantity;
    obj->hasDiscount = rand_bool(0);
    if (obj->hasDiscount) { /* Apply discount if there is some */
        obj->totalPrice *= (1.f - DRINK_DISCOUNT);
    }

	return (struct Article *) obj;
}

/* ************************************************************************* */
void Drink_destroy(struct Article *obj)
{
	Article_destroy(obj);
	free(obj);
}

/* *** Accessors : Getters ********* */
/* ************************************************************************* */
char * Drink_getName(struct Article * obj)
{
    return ((struct Drink *)obj)->name;
}

/* ************************************************************************* */
float Drink_getUnitPrice(struct Article * obj)
{
    return ((struct Drink *)obj)->unitPriceKg;
}

/* ************************************************************************* */
unsigned int Drink_getQuantity(struct Article * obj)
{
    return ((struct Drink *)obj)->quantity;
}

/* ************************************************************************* */
float Drink_getTotalPrice(struct Article * obj)
{
    return ((struct Drink *)obj)->totalPrice;
}

/* ************************************************************************* */
char Drink_getDiscountStatus(struct Article * obj)
{
    return ((struct Drink *)obj)->hasDiscount;
}

/* *** Accessors : Setters ********* */
/* ... */