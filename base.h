
#ifndef BASE_H
#define BASE_H

#include "object.h"


struct Base_VT {
    struct Object_VT base;
    void (*setX)(void *, int);
    int (*getX)(void *);
};


struct Base_data {
    struct Object_data base;
    int x;
};

void Base_data_construct(struct Base_data *data, int x);
void Base_data_destroy(void *data);

void Base_data_setX(void *data, int x);
int Base_data_getX(void *data);


typedef struct Base_TAG Base;

Base * Base_construct(int x);

void Base_setX(void *this, int x);
int Base_getX(void *this);


#endif
