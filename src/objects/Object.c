/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "CentralParts.h"
#include "objects/Object.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const struct ObjectClass _Object = {sizeof(struct Object), NULL, NULL, NULL};
const struct ObjectClass * __Object = & _Object;

// call all ctor's in the hierarchy of type
static Object * object_create_helper(const ObjectClass * ctype, Object * obj) {
    if (!obj || !ctype) {
        return NULL;
    }

    if (ctype->base) {
        if (ctype->ctor) {
            obj = object_create_helper(ctype->base, obj);
            if (obj) {
                return (Object *) ctype->ctor(obj);
            } else {
                return NULL;
            }
        } else {
            return obj;
        }
    } else {
        if (ctype->ctor) {
            return (Object *) ctype->ctor(obj);
        } else {
            return obj;
        }
    }
}

void * object_create_(const ObjectClass * ctype) {
    Object * obj = (Object *) mcx_malloc(ctype->size);
    if (!obj) {
        return NULL;
    }

    obj->_class = (ObjectClass *) ctype;
    obj->_refs  = 1;

    return object_create_helper(ctype, obj);
}

void object_destroy_(void ** self) {
    if (* self) {
        Object * obj = * (Object **) self;
        ObjectClass * cur_class = obj->_class;

        // not the last reference
        if (obj->_refs > 1) {
            obj->_refs -= 1;
            * self = NULL;
            return;
        }

        // last reference
        while (cur_class) {
            if (cur_class->dtor) {
                cur_class->dtor(obj);
            }
            cur_class = (ObjectClass *) cur_class->base;
        }

        mcx_free(obj);

        * self = NULL;
    }
}

void * object_strong_reference(void * self) {
    if (self) {
        Object * obj = (Object *) self;

        obj->_refs += 1;

        return obj;
    } else {
        return NULL;
    }
}

int object_same_type_(const struct ObjectClass * ctype, Object * obj) {
    return obj && obj->_class == ctype;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */