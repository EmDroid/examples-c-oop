
#ifndef OBJECT_H
#define OBJECT_H


typedef struct Object_TAG Object;


#define CALL_METHOD_0(type, method, obj)  \
    ((struct type ## _VT_TAG *)((struct Object_data *)obj)->vt)->method(obj)

#define CALL_METHOD_1(type, method, obj, par1)  \
    ((struct type ## _VT_TAG *)((struct Object_data *)obj)->vt)->method(obj, par1)


struct Object_VT_TAG {
    struct Object_VT_TAG *svt;
    size_t size;
    void (*destroy)(void *);
    void (*copy)(void *, void *);
};

extern struct Object_VT_TAG Object_VT;


void Object_VT_update(void *data, void *vt);


struct Object_data {
    void *guard;
    void *vt;
};


#define OBJECT_ALLOCATE(type) ((type *)Object_allocate(&type ## _VT))

#define NEW_DEFAULT(type) type ## _construct(OBJECT_ALLOCATE(type))

#define NEW_1(type, p1) type ## _construct(OBJECT_ALLOCATE(type), p1)
#define NEW_2(type, p1, p2) type ## _construct(OBJECT_ALLOCATE(type), p1, p2)
#define NEW_3(type, p1, p2, p3) type ## _construct(OBJECT_ALLOCATE(type), p1, p2, p3)
//etc.

#define NEW_CLONE(type, obj) (type *)Object_clone(obj)


Object * Object_allocate(void *size_data);
Object * Object_clone(void *obj);

void delete(void *obj);


#define IS_INSTANCE_OF(obj, type) Object_isInstanceOf(obj, &type ## _VT)

#define DYNAMIC_CAST(obj, type) ((type *)Object_dynamicCast(obj, &type ## _VT))

int Object_isInstanceOf(void *obj, void *type_vt);
void * Object_dynamicCast(void *obj, void *type_vt);


#endif
