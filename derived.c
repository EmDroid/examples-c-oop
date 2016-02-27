
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "derived.h"


typedef struct Derived_TAG {
    struct Derived_data data;
} Derived;


Derived * Derived_construct(Derived *self, int x, int y)
{
    assert(self != NULL);
    Base_construct((Base *)self, x);
    Object_VT_update(self, &Derived_VT);
    self->data.y = y;
    return self;
}


static void Derived_destroy(void *this)
{
    printf("Derived::destroy()\n");
}


static void Derived_copy(void *this, void *other)
{
    printf("Derived::copy()\n");
}


static void Derived_setX(Derived *this, int x)
{
    printf("Derived::setX()\n");
    Base_VT.setX(this, x);
}


static int Derived_getX(Derived *this)
{
    printf("Derived::getX()\n");
    return Base_VT.getX(this);
}


static void Derived_setY(Derived *this, int y)
{
    printf("Derived::setY()\n");
    this->data.y = y;
}


static int Derived_getY(Derived *this)
{
    printf("Derived::getY()\n");
    return this->data.y;
}


struct Derived_VT_TAG Derived_VT = {
    (struct Object_VT_TAG *)&Base_VT,
    sizeof(Derived),
    &Derived_destroy,
    &Derived_copy,
    &Derived_setX,
    &Derived_getX,
    &Derived_setY,
    &Derived_getY
};
