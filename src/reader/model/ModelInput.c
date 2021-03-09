/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/ModelInput.h"

#include "reader/model/components/ComponentsInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ModelInputDestructor(ModelInput * input) {
    if (input->components) { object_destroy(input->components); }
    if (input->connections) { object_destroy(input->connections); }
}

static ModelInput * ModelInputCreate(ModelInput * input) {
    input->components = NULL;
    input->connections = NULL;

    return input;
}

OBJECT_CLASS(ModelInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */