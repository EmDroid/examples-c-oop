
#ifndef OBJECT_H
#define OBJECT_H


struct Object_VT {
    void (*destructor)(void *obj);
};

void Object_VT_update(void *data, void *vt);


struct Object_data {
    void *vt;
};

void Object_data_destroy(void * this);


typedef struct Object_TAG Object;

Object * Object_allocate(size_t size);


#define new(type) type ## _construct

void delete(void *obj);


#endif
