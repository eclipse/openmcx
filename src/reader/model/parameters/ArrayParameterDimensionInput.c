/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/parameters/ArrayParameterDimensionInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ArrayParameterDimensionInputDestructor(ArrayParameterDimensionInput * input) {
}

static ArrayParameterDimensionInput * ArrayParameterDimensionInputCreate(ArrayParameterDimensionInput * input) {
    input->start = 0;
    input->end = 0;

    return input;
}

OBJECT_CLASS(ArrayParameterDimensionInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */