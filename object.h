
#ifndef OBJECT_H
#define OBJECT_H


#define DECLARE_CLASS_BEGIN(name, base)         \
    typedef struct name ## _DATA_TAG {          \
        struct base ## _DATA_TAG super;


#define DECLARE_CLASS_END(name)                 \
    } name ## _DATA;                            \
    typedef struct name ## _TAG {               \
        char data[sizeof(struct name ## _DATA_TAG)]; \
    } name;


#define IMPLEMENT_CLASS(name)


#define DECLARE_CLASS_CONSTRUCTOR(name) \
    extern DEFINE_CLASS_CONSTRUCTOR(name)

#define DEFINE_CLASS_CONSTRUCTOR(name) \
    name * name ## _construct


#define DECLARE_CLASS_VTABLE_BEGIN(name, base)  \
    struct name ## _VT_TAG {                    \
        struct base ## _VT_TAG base;


#define DECLARE_CLASS_VTABLE_END(name)          \
    };                                          \
    extern struct name ## _VT_TAG name ## _VT;


#define IMPLEMENT_CLASS_VTABLE_BEGIN(name, base)\
    struct name ## _VT_TAG name ## _VT = {      \
        (struct Object_VT_TAG *)&base ## _VT,   \
        sizeof(name),                           \
        &name ## _destroy,                      \
        &name ## _copy,


#define IMPLEMENT_CLASS_VTABLE_END(name)        \
    };


#define IMPLEMENT_DEFAULT_DESTRUCTOR(name)      \
    static void name ## _destroy(void *this)    \
    {                                           \
        printf(#name "::destroy()\n");          \
    }


#define IMPLEMENT_DEFAULT_COPY(name)                    \
    static void name ## _copy(void *this, void *other)  \
    {                                                   \
        printf(#name "::copy()\n");                     \
    }


typedef struct Object_TAG Object;


#define CALL_METHOD_0(type, method, obj)  \
    ((struct type ## _VT_TAG *)((struct Object_DATA_TAG *)obj)->vt)->method(obj)

#define CALL_METHOD_1(type, method, obj, par1)  \
    ((struct type ## _VT_TAG *)((struct Object_DATA_TAG *)obj)->vt)->method(obj, par1)


struct Object_VT_TAG {
    struct Object_VT_TAG *svt;
    size_t size;
    void (*destroy)(void *);
    void (*copy)(void *, void *);
};

extern struct Object_VT_TAG Object_VT;


void Object_VT_update(void *data, void *vt);


typedef struct Object_DATA_TAG {
    void *guard;
    void *vt;
} Object_DATA;

DECLARE_CLASS_CONSTRUCTOR(Object)(Object *self);


#define OBJECT_ALLOCATE(type) ((type *)Object_allocate(&type ## _VT))

#define CONSTRUCT_DEFAULT(type, var) type ## _construct(&var)

#define CONSTRUCT_1(type, var, p1) type ## _construct(&var, p1)
#define CONSTRUCT_2(type, var, p1, p2) type ## _construct(&var, p1, p2)
#define CONSTRUCT_3(type, var, p1, p2, p3) type ## _construct(&var, p1, p2, p3)
//etc.



#define NEW_DEFAULT(type) CONSTRUCT_DEFAULT(type, *OBJECT_ALLOCATE(type))

#define NEW_1(type, p1) CONSTRUCT_1(type, *OBJECT_ALLOCATE(type), p1)
#define NEW_2(type, p1, p2) CONSTRUCT_2(type, *OBJECT_ALLOCATE(type), p1, p2)
#define NEW_3(type, p1, p2, p3) CONSTRUCT_3(type, *OBJECT_ALLOCATE(type), p1, p2, p3)
//etc.

#define NEW_CLONE(type, obj) (type *)Object_clone(obj)


Object * Object_allocate(void *size_data);
Object * Object_clone(void *obj);

// run destructor without memory deallocation (objects built by CONSTRUCT_...)
void destroy(void *obj);

// run destructor and deallocate memory (objects built by NEW_...)
void delete(void *obj);


#define IS_INSTANCE_OF(obj, type) Object_isInstanceOf(obj, &type ## _VT)

#define DYNAMIC_CAST(obj, type) ((type *)Object_dynamicCast(obj, &type ## _VT))

int Object_isInstanceOf(void *obj, void *type_vt);
void * Object_dynamicCast(void *obj, void *type_vt);


#endif
