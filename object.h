
#ifndef OBJECT_H
#define OBJECT_H


typedef struct Object_TAG Object;

Object * Object_allocate(size_t size);
Object * Object_construct();
void Object_destroy(void * this);


#define new(type) type ## _construct

void delete(void *obj);


#endif
