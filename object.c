
#include <stdlib.h>
#include <stdio.h>

#include "object.h"


Object * Object_allocate(size_t size)
{
    Object * obj = (Object *)malloc(size);
    if (!obj) {
        fprintf(stderr, "Exception: Out of memory\n");
        abort();
    }
    return obj;
}


void delete(void *obj)
{
    free(obj);
}
