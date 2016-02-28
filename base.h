
#ifndef BASE_H
#define BASE_H

#include "object.h"


DECLARE_CLASS_BEGIN(Base, Object)
    // the attributes
    int x;
DECLARE_CLASS_END(Base)

DECLARE_CLASS_CONSTRUCTOR(Base)(Base *self, int x);

DECLARE_CLASS_VTABLE_BEGIN(Base, Object)
    // the methods
    void (*setX)(void *, int);
    int (*getX)(void *);
DECLARE_CLASS_VTABLE_END(Base)


#endif
