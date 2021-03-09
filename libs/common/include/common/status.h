/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_COMMON_STATUS_H
#define MCX_COMMON_STATUS_H

#include <stddef.h>


#define SIZE_T_ERROR (size_t)(-1)


typedef enum {
    RETURN_OK = 1,
    RETURN_ERROR = 0,
    RETURN_WARNING = -1,
} McxStatus;


#endif // !MCX_COMMON_STATUS_H