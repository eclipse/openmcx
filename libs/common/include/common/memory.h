/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_COMMON_MEMORY_H
#define MCX_COMMON_MEMORY_H

#include <stddef.h>


#define mcx_malloc(len) _mcx_malloc(len, __FUNCTION__)
#define mcx_free(obj) _mcx_free(obj, __FUNCTION__)
#define mcx_realloc(obj, len) _mcx_realloc(obj, len, __FUNCTION__)
#define mcx_calloc(num, size) _mcx_calloc(num, size, __FUNCTION__)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


extern void * _mcx_malloc(size_t, const char *);
extern void   _mcx_free(void *, const char *);
extern void * _mcx_calloc(size_t, size_t, const char *);
extern void * _mcx_realloc(void *, size_t, const char *);


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // !MCX_COMMON_MEMORY_H