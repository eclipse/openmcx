/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_OBJECTS_MAP_H
#define MCX_OBJECTS_MAP_H

#include "CentralParts.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************************************/
/*                                     hash bucket sizes                                         */
/*************************************************************************************************/
#define MC_SIZET_SIZET_MAP_HASH_SIZE 100

/*************************************************************************************************/
/*                         (size_t, size_t) key-value pair                                       */
/*************************************************************************************************/
struct SizeTSizeTElem {
    struct SizeTSizeTElem *next_;
    size_t key;
    size_t value;
};

typedef struct SizeTSizeTElem SizeTSizeTElem;

/*************************************************************************************************/
/*                              size_t -> size_t dictionary                                      */
/*************************************************************************************************/
typedef struct SizeTSizeTMap SizeTSizeTMap;

typedef SizeTSizeTElem* (*fSizeTSizeTMapAdd)(SizeTSizeTMap *map, size_t key, size_t value);
typedef SizeTSizeTElem* (*fSizeTSizeTMapGet)(SizeTSizeTMap *map, size_t key);

extern const struct ObjectClass _SizeTSizeTMap;

struct SizeTSizeTMap {
    Object _;

    // Adds a new key-value pair to the map. If the key already exists, the value will be overwritten
    // Returns the added key-value pair or NULL if an error occurred.
    fSizeTSizeTMapAdd Add;

    // Returns the kay-value pair from the map given a key. If the given key is not stored in the
    // map, NULL will be returned.
    fSizeTSizeTMapGet Get;

    SizeTSizeTElem *hash_table_[MC_SIZET_SIZET_MAP_HASH_SIZE];
};

#ifdef __cplusplus
}
#endif

#endif // !MCX_OBJECTS_MAP_H