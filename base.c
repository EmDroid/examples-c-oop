
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "base.h"


static struct Base_VT vt = {
    &Base_data_destroy,
    &Base_data_setX,
    &Base_data_getX
};

typedef struct Base_TAG {
    struct Base_data data;
} Base;


void Base_data_construct(struct Base_data *data, int x)
{
    assert(data != NULL);
    Object_VT_update(data, &vt);
    data->x = x;
}


void Base_data_destroy(void *data)
{
    Object_VT_update(data, &vt);
    printf("Base::destroy()\n");
    Object_data_destroy(data);
}


void Base_data_setX(void *data, int x)
{
    printf("Base::setX()\n");
    ((struct Base_data *)data)->x = x;
}

int Base_data_getX(void *data)
{
    printf("Base::getX()\n");
    return ((struct Base_data *)data)->x;
}


Base * Base_construct(int x)
{
    Base * obj = (Base *)Object_allocate(sizeof(Base));
    assert(obj != NULL);
    Base_data_construct(&obj->data, x);
    return obj;
}


void Base_setX(void *this, int x)
{
    (*(struct Base_VT **)this)->setX(this, x);
}


int Base_getX(void *this)
{
    return (*(struct Base_VT **)this)->getX(this);
}
