/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "objects/StringContainer.h"
#include "util/stdlib.h"
#include "CentralParts.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

McxStatus StringContainerInit(StringContainer * container, const size_t numElements) {
    size_t i = 0;

    container->counter = 0;

    container->numElements = numElements;

    if (numElements > 0) {
        container->keys = (char * *) mcx_calloc(numElements, sizeof(char *));
        container->values = (void * *) mcx_calloc(numElements, sizeof(void *));

        for (i = 0; i < numElements; i++) {
            container->keys[i] = NULL;
            container->values[i] = NULL;
        }
    } else {
        container->keys = NULL;
        container->values = NULL;
    }

    return RETURN_OK;
}


McxStatus StringContainerResize(StringContainer * container, const size_t numElements) {
    size_t i = 0;

    for (i = numElements; i < container->numElements; i++) {
        if (NULL != container->keys[i]) {
            mcx_free(container->keys[i]);
        }
    }
    if (numElements > 0) {
        container->keys = (char * *) mcx_realloc(container->keys, numElements * sizeof(char *));
        if (NULL == container->keys) {
            mcx_log(LOG_ERROR, "StringContainer: realloc of keys (%d elements) returned null-pointer", numElements);
            return RETURN_ERROR;
        }

        container->values = (void * *) mcx_realloc(container->values, numElements * sizeof(void *));
        if (NULL == container->values) {
            mcx_log(LOG_ERROR, "StringContainer: realloc of values (%d elements) returned null-pointer", numElements);
            return RETURN_ERROR;
        }

        for (i = container->numElements; i < numElements; i++) {
            container->keys[i] = NULL;
            container->values[i] = NULL;
        }
    } else {
        if (container->keys) {
            mcx_free(container->keys);
            container->keys = NULL;
        }
        if (container->values) {
            mcx_free(container->values);
            container->values = NULL;
        }
    }

    container->numElements = numElements;

    return RETURN_OK;
}


size_t StringContainerGetNumElements(StringContainer * container) {
    return container->numElements;
}


StringContainer * StringContainerCreate(const size_t numElements) {
    StringContainer * container = (StringContainer *) mcx_malloc(sizeof(StringContainer));

    StringContainerInit(container, numElements);

    return container;
}

McxStatus StringContainerSetString(StringContainer * container, const size_t idx, const char * key) {
    char * buffer = NULL;
    if (idx >= container->numElements) {
        mcx_log(LOG_ERROR, "StringContainer: SetString: Index %u out of bounds, number of elements is %u", container->counter, container->numElements);
        return RETURN_ERROR;
    }

    if (key) {
        buffer = (char *) mcx_calloc(strlen(key) + 1, sizeof(char));
        if (NULL == buffer) {
            mcx_log(LOG_ERROR, "StringContainer: SetString: Memory allocation failed");
            return RETURN_ERROR;
        }
        if (NULL != container->keys[idx]) {
            mcx_free(container->keys[idx]);
        }
        strcpy(buffer, key);
    }
    container->keys[idx] = buffer;

    container->values[idx] = NULL;

    return RETURN_OK;
}

McxStatus StringContainerAddString(StringContainer * container, const char * key) {
    McxStatus retVal;

    if (container->counter < 0 || container->counter >= container->numElements) {
        mcx_log(LOG_ERROR, "StringContainer: AddString: Counter %u out of bounds, number of elements is %u", container->counter, container->numElements);
        return RETURN_ERROR;
    }

    retVal = StringContainerSetString(container, container->counter, key);
    if (RETURN_OK == retVal) {
        container->counter ++;
    }

    return retVal;
}


McxStatus StringContainerSetKeyValue(StringContainer * container, const size_t idx, const char * key, void * value) {

    McxStatus retVal = StringContainerSetString(container, idx, key);

    if (RETURN_OK == retVal) {
        container->values[idx] = value;
    }

    return retVal;
}


const char * StringContainerGetString(StringContainer * container, const size_t idx) {
    if (idx >= container->numElements) {
        return NULL;
    }

    return container->keys[idx];
}


int StringContainerGetIndex(const StringContainer * container, const char * key) {
    int i = 0;

    /*
     * We rely on the assumption that the strings are unique.
     */
    for (i = 0; (size_t)i < container->numElements; i++) {
        if (container->keys[i] && 0 == strcmp(container->keys[i], key)) {
            return i;
        }
    }
    return -1;
}


void * StringContainerGetValue(const StringContainer * container, const char * key) {
    size_t i = 0;

    // we rely on the assumption that the strings are unique

    for (i = 0; i < container->numElements; i++) {
        if (container->keys[i]) {
            if (0 == strcmp(container->keys[i], key)) {
                return container->values[i];
            }
        }
    }
    return NULL;
}

void * StringContainerGetValueFromIndex(const StringContainer * container, size_t index) {
    // we rely on the assumption that the strings are unique
    if (index < container->numElements) {
        return container->values[index];
    }

    return NULL;
}



void StringContainerDestroy(StringContainer * container) {
    size_t i = 0;

    if (0 == container->numElements) {
        return;
    }

    for (i = 0; i < container->numElements; i++) {
        if (NULL != container->keys[i]) {
            mcx_free(container->keys[i]);
            container->keys[i] = NULL;
        }
    }
    if (container->values) {
        mcx_free(container->values);
        container->values = NULL;
    }
    if (NULL != container->keys) {
        mcx_free(container->keys);
        container->keys = NULL;
    }
    container->numElements = 0;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */