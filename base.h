
#ifndef BASE_H
#define BASE_H

#include "object.h"


struct Base_data {
    int x;
};

void Base_data_construct(struct Base_data *data, int x);


typedef struct Base_TAG Base;

Base * Base_construct(int x);

void Base_setX(void * this, int x);
int Base_getX(void * this);


#endif
