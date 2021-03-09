/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "storage/Backends.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const char * GetBackendTypeString(BackendType type) {
    switch (type) {
        case BACKEND_CSV:
            return "csv";
    }

    return "unknown";
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */