
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "object.h"
#include "base.h"
#include "derived.h"


static int getYorX(Base *obj)
{
    if (IS_INSTANCE_OF(obj, Derived))
        return CALL_METHOD_0(Derived, getY, obj);
    else
        return CALL_METHOD_0(Base, getX, obj);
}


DECLARE_CLASS_BEGIN(Derived2, Derived)
    // the attributes
    int z;
DECLARE_CLASS_END(Derived2)

DECLARE_CLASS_CONSTRUCTOR(Derived2)(Derived2 *self, int x, int y, int z);

DECLARE_CLASS_VTABLE_BEGIN(Derived2, Derived)
    // the methods
    void (*setZ)(void *, int);
    int (*getZ)(void *);
DECLARE_CLASS_VTABLE_END(Derived2)


IMPLEMENT_CLASS(Derived2)


DEFINE_CLASS_CONSTRUCTOR(Derived2)(Derived2 *self, int x, int y, int z)
{
    assert(self != NULL);
    // call parent constructor
    Derived_construct((Derived *)self, x, y);
    // bring the VT to current type
    Object_VT_update(self, &Derived2_VT);
    // set the members
    self->data.z = z;
    return self;
}


IMPLEMENT_DEFAULT_DESTRUCTOR(Derived2)
IMPLEMENT_DEFAULT_COPY(Derived2)


static void Derived2_setX(Derived2 *this, int x)
{
    printf("Derived2::setX()\n");
    Base_VT.setX(this, x);
}


static int Derived2_getX(Derived2 *this)
{
    printf("Derived2::getX()\n");
    return Base_VT.getX(this);
}


static void Derived2_setY(Derived2 *this, int y)
{
    printf("Derived2::setY()\n");
    Derived_VT.setY(this, y);
}


static int Derived2_getY(Derived2 *this)
{
    printf("Derived2::getY()\n");
    return Derived_VT.getY(this);
}


static void Derived2_setZ(Derived2 *this, int z)
{
    printf("Derived2::setZ()\n");
    this->data.z = z;
}


static int Derived2_getZ(Derived2 *this)
{
    printf("Derived2::getZ()\n");
    return this->data.z;
}


IMPLEMENT_CLASS_VTABLE_BEGIN(Derived2, Derived)
    &Derived2_setX,
    &Derived2_getX,
    &Derived2_setY,
    &Derived2_getY,
    &Derived2_setZ,
    &Derived2_getZ
IMPLEMENT_CLASS_VTABLE_END(Derived2)


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
    Derived2 *d2;

    b = NEW_1(Base, 1);
    test(CALL_METHOD_0(Base, getX, b), 1, "%d");
    CALL_METHOD_1(Base, setX, b, 2);
    test(CALL_METHOD_0(Base, getX, b), 2, "%d");
    test(IS_INSTANCE_OF(b, Base), 1, "%d");
    test(IS_INSTANCE_OF(b, Derived), 0, "%d");
    test(IS_INSTANCE_OF(b, Derived2), 0, "%d");
    test(DYNAMIC_CAST(b, Base), b, "%p");
    test(DYNAMIC_CAST(b, Derived), 0, "%p");
    test(DYNAMIC_CAST(b, Derived2), 0, "%p");
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
    test(IS_INSTANCE_OF(d, Derived2), 0, "%d");
    test(DYNAMIC_CAST(d, Base), (Base *)d, "%p");
    test(DYNAMIC_CAST(d, Derived), d, "%p");
    test(DYNAMIC_CAST(d, Derived2), 0, "%p");
    delete(d);
    d = NULL;

    d2 = NEW_3(Derived2, 13, 14, 15);
    test(CALL_METHOD_0(Base, getX, d2), 13, "%d");
    test(CALL_METHOD_0(Derived, getY, d2), 14, "%d");
    test(CALL_METHOD_0(Derived2, getZ, d2), 15, "%d");
    CALL_METHOD_1(Base, setX, d2, 25);
    CALL_METHOD_1(Derived, setY, d2, 26);
    CALL_METHOD_1(Derived2, setZ, d2, 27);
    test(CALL_METHOD_0(Base, getX, d2), 25, "%d");
    test(CALL_METHOD_0(Derived, getY, d2), 26, "%d");
    test(CALL_METHOD_0(Derived2, getZ, d2), 27, "%d");
    test(IS_INSTANCE_OF(d2, Base), 1, "%d");
    test(IS_INSTANCE_OF(d2, Derived), 1, "%d");
    test(IS_INSTANCE_OF(d2, Derived2), 1, "%d");
    test(DYNAMIC_CAST(d2, Base), (Base *)d2, "%p");
    test(DYNAMIC_CAST(d2, Derived), (Derived *)d2, "%p");
    test(DYNAMIC_CAST(d2, Derived2), d2, "%p");
    delete(d2);
    d2 = NULL;

    b = (Base *)NEW_2(Derived, 10, 11);
    test(CALL_METHOD_0(Base, getX, b), 10, "%d");
    CALL_METHOD_1(Base, setX, b, 12);
    test(CALL_METHOD_0(Base, getX, b), 12, "%d");
    test(IS_INSTANCE_OF(b, Base), 1, "%d");
    test(IS_INSTANCE_OF(b, Derived), 1, "%d");
    test(DYNAMIC_CAST(b, Base), b, "%p");
    test(DYNAMIC_CAST(b, Derived), (Derived *)b, "%p");
    test(getYorX(b), 11, "%d");

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
    test(getYorX(b1), 11, "%d");

    delete(b1);
    b1 = NULL;

    b = (Base *)NEW_3(Derived2, 100, 101, 102);
    test(CALL_METHOD_0(Base, getX, b), 100, "%d");
    CALL_METHOD_1(Base, setX, b, 120);
    test(CALL_METHOD_0(Base, getX, b), 120, "%d");
    test(IS_INSTANCE_OF(b, Base), 1, "%d");
    test(IS_INSTANCE_OF(b, Derived), 1, "%d");
    test(IS_INSTANCE_OF(b, Derived2), 1, "%d");
    test(DYNAMIC_CAST(b, Base), b, "%p");
    test(DYNAMIC_CAST(b, Derived), (Derived *)b, "%p");
    test(DYNAMIC_CAST(b, Derived2), (Derived2 *)b, "%p");

    b1 = NEW_CLONE(Base, b);

    delete(b);
    b = NULL;

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
