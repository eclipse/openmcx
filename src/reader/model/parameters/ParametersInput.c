/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/parameters/ParametersInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ParametersInputDestructor(ParametersInput * input) {
    if (input->parameters) {
        input->parameters->DestroyObjects(input->parameters);
        object_destroy(input->parameters);
    }
}

static ParametersInput * ParametersInputCreate(ParametersInput * input) {
    input->parameters = object_create(ObjectContainer);

    if (!input->parameters) {
        return NULL;
    }

    return input;
}

OBJECT_CLASS(ParametersInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */