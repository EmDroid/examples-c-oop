
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "object.h"


static struct Object_VT vt = {
    &Object_data_destroy
};

typedef struct Object_TAG {
    struct Object_data data;
} Object;


void Object_VT_update(void *data, void *vt)
{
    assert(data != NULL);
    assert(vt != NULL);
    ((struct Object_data *)data)->vt = vt;
}


void Object_data_destroy(void *data)
{
    Object_VT_update(data, &vt);
    printf("Object::destroy()\n");
}


Object * Object_allocate(size_t size)
{
    Object * obj = (Object *)malloc(size);
    if (!obj) {
        fprintf(stderr, "Exception: Out of memory\n");
        abort();
    }
    Object_VT_update(obj, &vt);
    return obj;
}


void delete(void *obj)
{
    if (obj)
    {
        struct Object_VT *vt = ((Object *)obj)->data.vt;
        assert(vt != NULL);
        if (!vt->destructor)
        {
            fprintf(stderr, "Pure virtual function call!\n");
            abort();
        }
        vt->destructor(obj);
    }
    free(obj);
}
