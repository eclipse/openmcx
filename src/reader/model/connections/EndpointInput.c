/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/connections/EndpointInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void VectorEndpointInputDestructor(VectorEndpointInput * input) {
    if (input->component) { mcx_free(input->component); }
    if (input->channel) { mcx_free(input->channel); }
}

static VectorEndpointInput * VectorEndpointInputCreate(VectorEndpointInput * input) {
    input->component = NULL;
    input->channel = NULL;
    input->startIndex = -1;
    input->endIndex = -1;

    return input;
}

OBJECT_CLASS(VectorEndpointInput, InputElement);

static void ScalarEndpointInputDestructor(ScalarEndpointInput * input) {
    if (input->component) { mcx_free(input->component); }
    if (input->channel) { mcx_free(input->channel); }
}

static ScalarEndpointInput * ScalarEndpointInputCreate(ScalarEndpointInput * input) {
    input->component = NULL;
    input->channel = NULL;

    return input;
}

OBJECT_CLASS(ScalarEndpointInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */