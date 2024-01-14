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

#include "util/stdlib.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


void mcx_sort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *, void *), void *arg) {
    qsort_r(base, nmemb, size, compar, arg);
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */