
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"


DECLARE_CLASS_BEGIN(Derived, Base)
    // the attributes
    int y;
DECLARE_CLASS_END(Derived)

DECLARE_CLASS_CONSTRUCTOR(Derived)(Derived *self, int x, int y);

DECLARE_CLASS_VTABLE_BEGIN(Derived, Base)
    // the methods
    void (*setY)(void *, int);
    int (*getY)(void *);
DECLARE_CLASS_VTABLE_END(Derived)


#endif
