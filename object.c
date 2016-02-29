
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

#include "object.h"


typedef struct Object_TAG {
    struct Object_DATA_TAG data;
} Object;


DEFINE_CLASS_CONSTRUCTOR(Object)(Object *self)
{
    assert(self != NULL);
    // put the guard
    ((Object_DATA *)&self->data)->guard = &Object_VT;
    // the initial Object virtual table
    Object_VT_update(self, &Object_VT);
    return self;
}


static void Object_destroy(void *this)
{
    printf("Object::destroy()\n");
}


static void Object_copy(void *this, void *other)
{
    printf("Object::copy()\n");
}


struct Object_VT_TAG Object_VT = {
    NULL,
    sizeof(Object),
    &Object_destroy,
    &Object_copy
};


void Object_VT_update(void *this, void *vt)
{
    assert(this != NULL);
    assert(vt != NULL);
    ((Object *)this)->data.vt = vt;
}


Object * Object_allocate(void *size_data)
{
    size_t size;
    Object * obj;
    assert(size_data != NULL);
    size = ((struct Object_VT_TAG *)size_data)->size;
    obj = (Object *)malloc(size);
    if (!obj) {
        fprintf(stderr, "Exception: Out of memory\n");
        abort();
    }
    memset(obj, 0, size);
    Object_construct(obj);
    return obj;
}


static void copy_construct(void *dst, void *src, struct Object_VT_TAG *vt)
{
    if (vt)
    {
        // call superclass copy first
        copy_construct(dst, src, vt->svt);
        // now set the virtual table to the current level
        ((Object *)dst)->data.vt = vt;
        // call the copy on the current level
        vt->copy(dst, src);
    }
}


Object * Object_clone(void *src)
{
    Object *dst;
    struct Object_VT_TAG *vt;

    if (!src) return NULL;

    // or runtime check and abort()
    assert(IS_INSTANCE_OF(src, Object));

    vt = ((struct Object_DATA_TAG *)src)->vt;
    dst = Object_allocate(vt);

    // by default, binary (shallow) copy is done
    // inherited class can supply copy() to provide different semantics
    memcpy(dst, src, vt->size);
    copy_construct(dst, src, vt);

    return dst;
}


void destroy(void *obj)
{
    struct Object_VT_TAG *vt;

    // or runtime check and abort()
    assert(IS_INSTANCE_OF(obj, Object));

    vt = ((struct Object_DATA_TAG *)obj)->vt;
    while (vt)
    {
        if (!vt->destroy)
        {
            fprintf(stderr, "Pure virtual function call!\n");
            abort();
        }
        vt->destroy(obj);
        // move VT to superclass (will continue calling parent destructor)
        ((struct Object_DATA_TAG *)obj)->vt = vt = vt->svt;
    }
}


void delete(void *obj)
{
    if (obj) destroy(obj);

    free(obj);
}


int Object_isInstanceOf(void *obj, void *type_vt)
{
    struct Object_VT_TAG *obj_vt;
    assert(type_vt != NULL);
    if (!obj) return 0;

    // check if the guard matches and there is a nonzero VT table pointer
    if (*(void **)obj != &Object_VT || (*(void ***)obj + 1) == NULL) return 0;

    // note the above still can fail in some cases - to solve this properly,
    // building of registry of all know VTs woould need to be done and the
    // object checked against that registry
    // (the registry can be build/updated by Object_allocate() which is to
    // be called for each valid object)

    obj_vt = ((struct Object_DATA_TAG *)obj)->vt;
    while (obj_vt)
    {
        if (obj_vt == type_vt) return 1;
        obj_vt = obj_vt->svt;
    }
    return 0;
}


void * Object_dynamicCast(void *obj, void *type_vt)
{
    return Object_isInstanceOf(obj, type_vt) ? obj : NULL;
}
