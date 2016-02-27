
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "derived.h"


static struct Derived_VT vt = {
    &Derived_data_destroy,
    &Derived_data_setX,
    &Derived_data_getX,
    &Derived_data_setY,
    &Derived_data_getY
};


typedef struct Derived_TAG {
    struct Derived_data data;
} Derived;


void Derived_data_construct(struct Derived_data *data, int x, int y)
{
    assert(data != NULL);
    Base_data_construct(&data->base, x);
    Object_VT_update(data, &vt);
    data->y = y;
}


void Derived_data_destroy(void *data)
{
    Object_VT_update(data, &vt);
    printf("Derived::destroy()\n");
    Base_data_destroy(data);
}


void Derived_data_setX(void *data, int x)
{
    printf("Derived::setX()\n");
    Base_data_setX(data, x);
}


int Derived_data_getX(void *data)
{
    printf("Derived::getX()\n");
    return Base_data_getX(data);
}


void Derived_data_setY(void *data, int y)
{
    printf("Derived::setY()\n");
    ((struct Derived_data *)data)->y = y;
}


int Derived_data_getY(void *data)
{
    printf("Derived::getY()\n");
    return ((struct Derived_data *)data)->y;
}


Derived * Derived_construct(int x, int y)
{
    Derived * obj = (Derived *)Object_allocate(sizeof(Derived));
    assert(obj != NULL);
    Derived_data_construct(&obj->data, x, y);
    return obj;
}


void Derived_setY(void *this, int y)
{
    (*(struct Derived_VT **)this)->setY(this, y);
}


int Derived_getY(void *this)
{
    return (*(struct Derived_VT **)this)->getY(this);
}
