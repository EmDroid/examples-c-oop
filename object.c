
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

#include "object.h"


typedef struct Object_TAG {
    struct Object_data data;
} Object;


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
    // the initial Object virtual table
    Object_VT_update(obj, &Object_VT);
    return obj;
}


static void copy_construct(void *dst, void *src, struct Object_VT_TAG *vt)
{
    if (vt)
    {
        // call superclass copy first
        copy_construct(dst, src, vt->svt);
        // now set the virtual table to the current level
        *(struct Object_VT_TAG **)dst = vt;
        // call the copy on the current level
        vt->copy(dst, src);
    }
}


Object * Object_clone(void *src)
{
    Object *dst;
    struct Object_VT_TAG *vt;

    if (!src) return NULL;

    vt = *(struct Object_VT_TAG **)src;
    dst = Object_allocate(vt);

    // by default, binary (shallow) copy is done
    // inherited class can supply copy() to provide different semantics
    memcpy(dst, src, vt->size);
    copy_construct(dst, src, vt);

    return dst;
}


void delete(void *obj)
{
    if (obj)
    {
        struct Object_VT_TAG *vt = *(struct Object_VT_TAG **)obj;
        while (vt)
        {
            if (!vt->destroy)
            {
                fprintf(stderr, "Pure virtual function call!\n");
                abort();
            }
            vt->destroy(obj);
            // move VT to superclass (will continue calling parent destructor)
            *(struct Object_VT_TAG **)obj = vt = vt->svt;
        }
    }
    free(obj);
}
