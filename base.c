
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "base.h"


typedef struct Base_TAG {
    struct Base_data data;
} Base;


Base * Base_construct(Base *self, int x)
{
    assert(self != NULL);
    Object_VT_update(self, &Base_VT);
    self->data.x = x;
    return self;
}


static void Base_destroy(void *this)
{
    printf("Base::destroy()\n");
}


static void Base_copy(void *this, void *other)
{
    printf("Base::copy()\n");
}


static void Base_setX(Base *this, int x)
{
    printf("Base::setX()\n");
    this->data.x = x;
}


static int Base_getX(Base *this)
{
    printf("Base::getX()\n");
    return this->data.x;
}


struct Base_VT_TAG Base_VT = {
    (struct Object_VT_TAG *)&Object_VT,
    sizeof(Base),
    &Base_destroy,
    &Base_copy,
    &Base_setX,
    &Base_getX
};
