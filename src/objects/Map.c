/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "objects/Map.h"

size_t SizeTSizeTHash(size_t value) {
    return value % MC_SIZET_SIZET_MAP_HASH_SIZE;
}

SizeTSizeTElem* SizeTSizeTMapAdd(SizeTSizeTMap *map, size_t key, size_t value) {
    SizeTSizeTElem *elem = map->Get(map, key);

    if (elem == NULL) {
        elem = (SizeTSizeTElem*)mcx_malloc(sizeof(SizeTSizeTElem));
        if (elem == NULL) {
            return NULL;
        }
        elem->key = key;
        elem->value = value;

        size_t hash_val = SizeTSizeTHash(key);
        elem->next_ = map->hash_table_[hash_val];
        map->hash_table_[hash_val] = elem;
    } else {
        elem->value = value;
    }

    return elem;
}

SizeTSizeTElem* SizeTSizeTMapGet(SizeTSizeTMap *map, size_t key) {
    SizeTSizeTElem *elem = NULL;

    for (elem = map->hash_table_[SizeTSizeTHash(key)]; elem != NULL; elem = elem->next_) {
        if (elem->key == key) {
            return elem;
        }
    }

    return NULL;
}

static void SizeTSizeTMapDestructor(SizeTSizeTMap * map) {
    size_t i = 0;
    SizeTSizeTElem *elem = NULL, *elem_ = NULL;

    for (i = 0; i < MC_SIZET_SIZET_MAP_HASH_SIZE; ++i) {
        elem = map->hash_table_[i];

        if (elem == NULL) {
            continue;
        }

        while (elem != NULL) {
            elem_ = elem;
            elem = elem->next_;
            mcx_free(elem_);
        }
    }
}

static SizeTSizeTMap * SizeTSizeTMapCreate(SizeTSizeTMap * map) {
    size_t i = 0;

    for (i = 0; i < MC_SIZET_SIZET_MAP_HASH_SIZE; ++i) {
        map->hash_table_[i] = NULL;
    }

    map->Add = SizeTSizeTMapAdd;
    map->Get = SizeTSizeTMapGet;

    return map;
}

OBJECT_CLASS(SizeTSizeTMap, Object);