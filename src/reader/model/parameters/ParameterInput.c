/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/parameters/ParameterInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ParameterInputDestructor(ParameterInput * input) {
    if (input->parameter.arrayParameter) { object_destroy(input->parameter.arrayParameter); }
}

static ParameterInput * ParameterInputCreate(ParameterInput * input) {
    input->type = PARAMETER_ARRAY;
    input->parameter.arrayParameter = NULL;

    return input;
}

OBJECT_CLASS(ParameterInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */