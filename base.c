
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "base.h"


IMPLEMENT_CLASS(Base)


DEFINE_CLASS_CONSTRUCTOR(Base)(Base *self, int x)
{
    assert(self != NULL);
    Object_VT_update(self, &Base_VT);
    self->data.x = x;
    return self;
}


IMPLEMENT_DEFAULT_DESTRUCTOR(Base)
IMPLEMENT_DEFAULT_COPY(Base)


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


IMPLEMENT_CLASS_VTABLE_BEGIN(Base, Object)
    &Base_setX,
    &Base_getX
IMPLEMENT_CLASS_VTABLE_END(Base)
