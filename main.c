
#include <stdlib.h>
#include <stdio.h>

#include "object.h"
#include "base.h"
#include "derived.h"


int main(void)
{
    Base *b;
    Derived *d;

    b = new(Base)(1);
    printf("Base::getX(): %d\n", Base_getX(b));
    Base_setX(b, 2);
    printf("Base::getX(): %d\n", Base_getX(b));
    delete(b);

    d = new(Derived)(3, 4);
    printf("Base::getX(): %d\n", Base_getX(d));
    printf("Derived::getY(): %d\n", Derived_getY(d));
    Base_setX(d, 5);
    Derived_setY(d, 6);
    printf("Base::getX(): %d\n", Base_getX(d));
    printf("Derived::getY(): %d\n", Derived_getY(d));
    delete(d);

    b = (Base *)new(Derived)(10, 11);
    printf("Base::getX(): %d\n", Base_getX(b));
    Base_setX(b, 12);
    printf("Base::getX(): %d\n", Base_getX(b));
    delete(b);

    return 0;
}
