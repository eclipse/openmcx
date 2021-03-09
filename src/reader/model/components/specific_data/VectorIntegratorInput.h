/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_MODEL_COMPONENTS_SPECIFIC_DATA_VECTOR_INTEGRATOR_INPUT_H
#define MCX_READER_MODEL_COMPONENTS_SPECIFIC_DATA_VECTOR_INTEGRATOR_INPUT_H

#include "reader/model/components/ComponentInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern const ObjectClass _VectorIntegratorInput;

typedef struct VectorIntegratorInput {
    ComponentInput _;

    OPTIONAL_VALUE(double) initialState;
} VectorIntegratorInput;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_MODEL_COMPONENTS_SPECIFIC_DATA_VECTOR_INTEGRATOR_INPUT_H