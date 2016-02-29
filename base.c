
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "base.h"


IMPLEMENT_CLASS(Base)


DEFINE_CLASS_CONSTRUCTOR(Base)(Base *self, int x)
{
    assert(self != NULL);
    Object_construct((Object *)self);
    Object_VT_update(self, &Base_VT);
    ((Base_DATA *)&self->data)->x = x;
    return self;
}


IMPLEMENT_DEFAULT_DESTRUCTOR(Base)
IMPLEMENT_DEFAULT_COPY(Base)


static void Base_setX(void *this, int x)
{
    printf("Base::setX()\n");
    ((Base_DATA *)&((Base *)this)->data)->x = x;
}


static int Base_getX(void *this)
{
    printf("Base::getX()\n");
    return ((Base_DATA *)&((Base *)this)->data)->x;
}


IMPLEMENT_CLASS_VTABLE_BEGIN(Base, Object)
    &Base_setX,
    &Base_getX
IMPLEMENT_CLASS_VTABLE_END(Base)
