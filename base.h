
#ifndef BASE_H
#define BASE_H

#include "object.h"


typedef struct Base_TAG Base;


Base * Base_construct(Base *self, int x);


struct Base_VT_TAG {
    struct Object_VT_TAG base;
    void (*setX)(void *, int);
    int (*getX)(void *);
};

extern struct Base_VT_TAG Base_VT;


struct Base_data {
    struct Object_data base;
    int x;
};


#endif
