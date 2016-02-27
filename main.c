
#include <stdlib.h>
#include <stdio.h>

#include "object.h"
#include "base.h"
#include "derived.h"


int main(void)
{
    Base *b, *b1;
    Derived *d;

    b = NEW_1(Base, 1);
    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, b));
    CALL_METHOD_1(Base, setX, b, 2);
    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, b));
    delete(b);

    d = NEW_2(Derived, 3, 4);
    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, d));
    printf("Derived::getY(): %d\n", CALL_METHOD_0(Derived, getY, d));
    CALL_METHOD_1(Base, setX, d, 5);
    CALL_METHOD_1(Derived, setY, d, 6);
    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, d));
    printf("Derived::getY(): %d\n", CALL_METHOD_0(Derived, getY, d));
    delete(d);

    b = (Base *)NEW_2(Derived, 10, 11);
    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, b));
    CALL_METHOD_1(Base, setX, b, 12);
    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, b));

    b1 = NEW_CLONE(Base, b);

    delete(b);

    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, b1));
    CALL_METHOD_1(Base, setX, b1, 20);
    printf("Base::getX(): %d\n", CALL_METHOD_0(Base, getX, b1));

    delete(b1);

    return 0;
}
