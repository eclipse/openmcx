/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "Memory.h"

#include "tarjan.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* general wrapper over mcx_ macros */

void * mem_mcx_malloc(size_t size) {
    return mcx_malloc(size);
}
void * mem_mcx_realloc(void * obj, size_t size) {
    return mcx_realloc(obj, size);
}
void   mem_mcx_free(void * obj) {
    mcx_free(obj);
}


McxStatus InitMemory(void) {
    int statusFlag = 0;

    statusFlag = tarjan_init_mem(mem_mcx_malloc, mem_mcx_free, mem_mcx_realloc);
    if (statusFlag) {
        // no error message because logging not initialised
        return RETURN_ERROR;
    }

    return RETURN_OK;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */