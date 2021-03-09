/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/components/specific_data/IntegratorInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void IntegratorInputDestructor(IntegratorInput * input) {
}

static IntegratorInput * IntegratorInputCreate(IntegratorInput * input) {
    OPTIONAL_UNSET(input->gain);
    OPTIONAL_UNSET(input->numSubSteps);
    OPTIONAL_UNSET(input->initialState);

    return input;
}

OBJECT_CLASS(IntegratorInput, ComponentInput);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */