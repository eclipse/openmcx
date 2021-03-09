/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_OBJECTS_OBJECT_H
#define MCX_OBJECTS_OBJECT_H

#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct ObjectClass {
    size_t size;
    const struct ObjectClass * base;
    void * (* ctor) (void *);
    void   (* dtor) (void *);
} ObjectClass;


typedef struct Object {
    ObjectClass * _class;

    size_t _refs;
} Object;

extern const struct ObjectClass _Object;

#define OBJECT_CLASS(x, base) const struct ObjectClass _##x = {sizeof(struct x), &_##base, (void *(*)(void *)) x##Create, (void (*)(void *)) x##Destructor};

#define object_class_of(x) (&_##x)

#define object_create(x) object_create_(&_##x)
#define object_destroy(x) object_destroy_((void **)&(x))

#define object_same_type(class, obj) object_same_type_(&_##class, (Object *) obj)

void * object_create_(const ObjectClass * type);
void   object_destroy_(void ** self);

void * object_strong_reference(void * self);

int object_same_type_(const ObjectClass * type, Object * obj);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_OBJECTS_OBJECT_H */