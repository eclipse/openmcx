/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_MODEL_COMPONENTS_COMPONENT_RESULTS_INPUT_H
#define MCX_READER_MODEL_COMPONENTS_COMPONENT_RESULTS_INPUT_H

#include "reader/core/InputElement.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct ComponentResultsInput ComponentResultsInput;

typedef McxStatus (*fComponentResultsInputCopyFrom)(ComponentResultsInput * self, ComponentResultsInput * src);

extern const ObjectClass _ComponentResultsInput;

struct ComponentResultsInput {
    InputElement _;

    OPTIONAL_VALUE(int) rtFactor;

    OPTIONAL_VALUE(StoreLevel) resultLevel;

    OPTIONAL_VALUE(double) startTime;
    OPTIONAL_VALUE(double) endTime;
    OPTIONAL_VALUE(double) stepTime;
    OPTIONAL_VALUE(size_t) stepCount;

    fComponentResultsInputCopyFrom CopyFrom;
};

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_MODEL_COMPONENTS_COMPONENT_RESULTS_INPUT_H