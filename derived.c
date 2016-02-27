
#include <stdlib.h>
#include <assert.h>

#include "derived.h"


typedef struct Derived_TAG {
    struct Derived_data data;
} Derived;


void Derived_data_construct(struct Derived_data *data, int x, int y)
{
    assert(data != NULL);
    Base_data_construct(&data->base, x);
    data->y = y;
}


Derived * Derived_construct(int x, int y)
{
    Derived * obj = (Derived *)Object_allocate(sizeof(Derived));
    assert(obj != NULL);
    Derived_data_construct(&obj->data, x, y);
    return obj;
}


void Derived_setY(void * this, int y)
{
    ((Derived *)this)->data.y = y;
}

int Derived_getY(void * this)
{
    return ((Derived *)this)->data.y;
}
