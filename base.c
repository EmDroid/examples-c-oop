
#include <stdlib.h>
#include <assert.h>

#include "base.h"


typedef struct Base_TAG {
    struct Base_data data;
} Base;


void Base_data_construct(struct Base_data *data, int x)
{
    assert(data != NULL);
    data->x = x;
}


Base * Base_construct(int x)
{
    Base * obj = (Base *)Object_allocate(sizeof(Base));
    assert(obj != NULL);
    Base_data_construct(&obj->data, x);
    return obj;
}


void Base_setX(void * this, int x)
{
    ((Base *)this)->data.x = x;
}

int Base_getX(void * this)
{
    return ((Base *)this)->data.x;
}
