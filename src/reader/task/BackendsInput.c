/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/task/BackendsInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void BackendsInputDestructor(BackendsInput * input) {
    if (input->backends) {
        input->backends->DestroyObjects(input->backends);
        object_destroy(input->backends);
    }
}

static BackendsInput * BackendsInputCreate(BackendsInput * input) {
    input->backends = (ObjectContainer*)object_create(ObjectContainer);

    if (!input->backends) {
        return NULL;
    }

    return input;
}

OBJECT_CLASS(BackendsInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */