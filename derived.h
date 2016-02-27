
#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"


struct Derived_VT {
    struct Base_VT base;
    void (*setY)(void *, int);
    int (*getY)(void *);
};


struct Derived_data {
    struct Base_data base;
    int y;
};

void Derived_data_construct(struct Derived_data *data, int x, int y);
void Derived_data_destroy(void *data);

void Derived_data_setX(void *data, int x);
int Derived_data_getX(void *data);
void Derived_data_setY(void *data, int y);
int Derived_data_getY(void *data);


typedef struct Derived_TAG Derived;

Derived * Derived_construct(int x, int y);

void Derived_setY(void *this, int y);
int Derived_getY(void *this);


#endif
