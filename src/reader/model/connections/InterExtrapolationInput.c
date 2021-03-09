/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/connections/InterExtrapolationInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void InterExtrapolationInputDestructor(InterExtrapolationInput * input) {
}

static InterExtrapolationInput * InterExtrapolationInputCreate(InterExtrapolationInput * input) {
    input->extrapolationType = INTERVAL_SYNCHRONIZATION;
    input->interpolationType = INTERVAL_COUPLING;
    input->extrapolationOrder = POLY_CONSTANT;
    input->interpolationOrder = POLY_CONSTANT;

    return input;
}

OBJECT_CLASS(InterExtrapolationInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */