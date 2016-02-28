
#include <stdlib.h>
#include <stdio.h>

#include "object.h"
#include "base.h"
#include "derived.h"


static struct {
    char c;
} invalid1;


int main(void)
{
    Base *b, *b1;
    Derived *d;

    b = NEW_1(Base, 1);
    printf("b.getX(): %d\n", CALL_METHOD_0(Base, getX, b));
    CALL_METHOD_1(Base, setX, b, 2);
    printf("b.getX(): %d\n", CALL_METHOD_0(Base, getX, b));
    printf("IS_INSTANCE_OF(b, Base): %d\n", IS_INSTANCE_OF(b, Base));
    printf("IS_INSTANCE_OF(b, Derived): %d\n", IS_INSTANCE_OF(b, Derived));
    printf("DYNAMIC_CAST(b, Base): %p\n", DYNAMIC_CAST(b, Base));
    printf("DYNAMIC_CAST(b, Derived): %p\n", DYNAMIC_CAST(b, Derived));
    delete(b);
    b = NULL;

    d = NEW_2(Derived, 3, 4);
    printf("d.getX(): %d\n", CALL_METHOD_0(Base, getX, d));
    printf("d.getY(): %d\n", CALL_METHOD_0(Derived, getY, d));
    CALL_METHOD_1(Base, setX, d, 5);
    CALL_METHOD_1(Derived, setY, d, 6);
    printf("d.getX(): %d\n", CALL_METHOD_0(Base, getX, d));
    printf("d.getY(): %d\n", CALL_METHOD_0(Derived, getY, d));
    printf("IS_INSTANCE_OF(d, Base): %d\n", IS_INSTANCE_OF(d, Base));
    printf("IS_INSTANCE_OF(d, Derived): %d\n", IS_INSTANCE_OF(d, Derived));
    printf("DYNAMIC_CAST(d, Base): %p\n", DYNAMIC_CAST(d, Base));
    printf("DYNAMIC_CAST(d, Derived): %p\n", DYNAMIC_CAST(d, Derived));
    delete(d);
    d = NULL;

    b = (Base *)NEW_2(Derived, 10, 11);
    printf("b.getX(): %d\n", CALL_METHOD_0(Base, getX, b));
    CALL_METHOD_1(Base, setX, b, 12);
    printf("b.getX(): %d\n", CALL_METHOD_0(Base, getX, b));
    printf("IS_INSTANCE_OF(b, Base): %d\n", IS_INSTANCE_OF(b, Base));
    printf("IS_INSTANCE_OF(b, Derived): %d\n", IS_INSTANCE_OF(b, Derived));
    printf("DYNAMIC_CAST(b, Base): %p\n", DYNAMIC_CAST(b, Base));
    printf("DYNAMIC_CAST(b, Derived): %p\n", DYNAMIC_CAST(b, Derived));

    b1 = NEW_CLONE(Base, b);

    delete(b);
    b = NULL;

    printf("b1.getX(): %d\n", CALL_METHOD_0(Base, getX, b1));
    CALL_METHOD_1(Base, setX, b1, 20);
    printf("b1.getX(): %d\n", CALL_METHOD_0(Base, getX, b1));
    printf("IS_INSTANCE_OF(b1, Base): %d\n", IS_INSTANCE_OF(b1, Base));
    printf("IS_INSTANCE_OF(b1, Derived): %d\n", IS_INSTANCE_OF(b1, Derived));
    printf("DYNAMIC_CAST(b1, Base): %p\n", DYNAMIC_CAST(b1, Base));
    printf("DYNAMIC_CAST(b1, Derived): %p\n", DYNAMIC_CAST(b1, Derived));

    delete(b1);
    b1 = NULL;

    printf("IS_INSTANCE_OF(NULL, Base): %d\n", IS_INSTANCE_OF(NULL, Base));
    printf("IS_INSTANCE_OF(NULL, Derived): %d\n", IS_INSTANCE_OF(NULL, Derived));
    printf("DYNAMIC_CAST(NULL, Base): %p\n", DYNAMIC_CAST(NULL, Base));
    printf("DYNAMIC_CAST(NULL, Derived): %p\n", DYNAMIC_CAST(NULL, Derived));

    printf("IS_INSTANCE_OF(invalid1, Base): %d\n", IS_INSTANCE_OF(&invalid1, Base));
    printf("IS_INSTANCE_OF(invalid1, Derived): %d\n", IS_INSTANCE_OF(&invalid1, Derived));
    printf("DYNAMIC_CAST(invalid1, Base): %p\n", DYNAMIC_CAST(&invalid1, Base));
    printf("DYNAMIC_CAST(invalid1, Derived): %p\n", DYNAMIC_CAST(&invalid1, Derived));

//    delete(&invalid1);  // should assert in the deleter

    return 0;
}
