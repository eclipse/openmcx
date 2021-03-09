/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_OBJECTS_STRING_CONTAINER_H
#define MCX_OBJECTS_STRING_CONTAINER_H

#include "CentralParts.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// TODO: unify with MapStringInt
typedef struct StringContainer {
    size_t numElements;
    char * * keys;
    void * * values;  // TODO: using the StringContainer for additional data
    size_t counter;
} StringContainer;


StringContainer * StringContainerCreate(const size_t numElements);

McxStatus StringContainerInit(StringContainer * container, const size_t numElements);
McxStatus StringContainerSetString(StringContainer * container, const size_t idx, const char * key);
McxStatus StringContainerAddString(StringContainer * container, const char * key);
const char * StringContainerGetString(StringContainer * container, const size_t idx);
int StringContainerGetIndex(const StringContainer * container, const char * key);
void StringContainerDestroy(StringContainer * container);


// TODO: using the StringContainer for additional data
McxStatus StringContainerSetKeyValue(StringContainer * container, const size_t idx, const char * key, void * value);
void * StringContainerGetValue(const StringContainer * container, const char * key);
void * StringContainerGetValueFromIndex(const StringContainer * container, size_t index);
McxStatus StringContainerResize(StringContainer * container, const size_t numElements);
size_t StringContainerGetNumElements(StringContainer * container);


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_OBJECTS_STRING_CONTAINER_H */