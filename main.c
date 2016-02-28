
#include <stdlib.h>
#include <stdio.h>

#include "object.h"
#include "base.h"
#include "derived.h"


static struct {
    char c;
} invalid1;


#define test(what, result_expected, result_format)          \
    if ((what) != result_expected)                          \
    {                                                       \
        fprintf(stderr,                                     \
            "%s(%d): %s failed: result: " #result_format    \
            ", expected result: " #result_format "\n",      \
            __FILE__, __LINE__,                             \
            #what, (what), result_expected);                \
        return EXIT_FAILURE;                                \
    }



int main(void)
{
    Base *b, *b1;
    Derived *d;

    b = NEW_1(Base, 1);
    test(CALL_METHOD_0(Base, getX, b), 1, "%d");
    CALL_METHOD_1(Base, setX, b, 2);
    test(CALL_METHOD_0(Base, getX, b), 2, "%d");
    test(IS_INSTANCE_OF(b, Base), 1, "%d");
    test(IS_INSTANCE_OF(b, Derived), 0, "%d");
    test(DYNAMIC_CAST(b, Base), b, "%p");
    test(DYNAMIC_CAST(b, Derived), 0, "%p");
    delete(b);
    b = NULL;

    d = NEW_2(Derived, 3, 4);
    test(CALL_METHOD_0(Base, getX, d), 3, "%d");
    test(CALL_METHOD_0(Derived, getY, d), 4, "%d");
    CALL_METHOD_1(Base, setX, d, 5);
    CALL_METHOD_1(Derived, setY, d, 6);
    test(CALL_METHOD_0(Base, getX, d), 5, "%d");
    test(CALL_METHOD_0(Derived, getY, d), 6, "%d");
    test(IS_INSTANCE_OF(d, Base), 1, "%d");
    test(IS_INSTANCE_OF(d, Derived), 1, "%d");
    test(DYNAMIC_CAST(d, Base), (Base *)d, "%p");
    test(DYNAMIC_CAST(d, Derived), d, "%p");
    delete(d);
    d = NULL;

    b = (Base *)NEW_2(Derived, 10, 11);
    test(CALL_METHOD_0(Base, getX, b), 10, "%d");
    CALL_METHOD_1(Base, setX, b, 12);
    test(CALL_METHOD_0(Base, getX, b), 12, "%d");
    test(IS_INSTANCE_OF(b, Base), 1, "%d");
    test(IS_INSTANCE_OF(b, Derived), 1, "%d");
    test(DYNAMIC_CAST(b, Base), b, "%p");
    test(DYNAMIC_CAST(b, Derived), (Derived *)b, "%p");

    b1 = NEW_CLONE(Base, b);

    delete(b);
    b = NULL;

    test(CALL_METHOD_0(Base, getX, b1), 12, "%d");
    CALL_METHOD_1(Base, setX, b1, 20);
    test(CALL_METHOD_0(Base, getX, b1), 20, "%d");
    test(IS_INSTANCE_OF(b1, Base), 1, "%d");
    test(IS_INSTANCE_OF(b1, Derived), 1, "%d");
    test(DYNAMIC_CAST(b1, Base), b1, "%p");
    test(DYNAMIC_CAST(b1, Derived), (Derived *)b1, "%p");

    delete(b1);
    b1 = NULL;

    test(IS_INSTANCE_OF(NULL, Base), 0, "%d");
    test(IS_INSTANCE_OF(NULL, Derived), 0, "%d");
    test(DYNAMIC_CAST(NULL, Base), NULL, "%p");
    test(DYNAMIC_CAST(NULL, Derived), NULL, "%p");

    test(IS_INSTANCE_OF(&invalid1, Base), 0, "%d");
    test(IS_INSTANCE_OF(&invalid1, Derived), 0, "%d");
    test(DYNAMIC_CAST(&invalid1, Base), NULL, "%p");
    test(DYNAMIC_CAST(&invalid1, Derived), NULL, "%p");

//    delete(&invalid1);  // should assert in the deleter

    return 0;
}
