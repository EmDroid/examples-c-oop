
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"


typedef struct Derived_TAG Derived;


Derived * Derived_construct(Derived *self, int x, int y);


struct Derived_VT_TAG {
    struct Base_VT_TAG base;
    void (*setY)(void *, int);
    int (*getY)(void *);
};

extern struct Derived_VT_TAG Derived_VT;


struct Derived_data {
    struct Base_data base;
    int y;
};


#endif
