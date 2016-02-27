
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"


struct Derived_data {
    struct Base_data base;
    int y;
};

void Derived_data_construct(struct Derived_data *data, int x, int y);


typedef struct Derived_TAG Derived;

Derived * Derived_construct(int x, int y);

void Derived_setY(void * this, int y);
int Derived_getY(void * this);


#endif
