/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "util/time.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void mcx_time_init(McxTime * time) {
    McxTime now;
    mcx_time_get(&now);
    mcx_time_diff(&now, &now, time);
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */