/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/components/specific_data/VectorIntegratorInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void VectorIntegratorInputDestructor(VectorIntegratorInput * input) {
}

static VectorIntegratorInput * VectorIntegratorInputCreate(VectorIntegratorInput * input) {
    OPTIONAL_UNSET(input->initialState);

    return input;
}

OBJECT_CLASS(VectorIntegratorInput, ComponentInput);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */