/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/components/specific_data/FmuInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void FmuInputDestructor(FmuInput * input) {
    if (input->fmuFile) { mcx_free(input->fmuFile); }
    if (input->logCategories) {
        size_t i = 0;
        for (i = 0; i < input->numLogCategories; i++) {
            mcx_free(input->logCategories[i]);
        }
        mcx_free(input->logCategories);
        input->numLogCategories = 0;
    }
}


static FmuInput * FmuInputCreate(FmuInput * input) {
    input->fmuFile = NULL;
    OPTIONAL_UNSET(input->isLogging);

    input->numLogCategories = 0;
    input->logCategories = NULL;

    OPTIONAL_UNSET(input->modelInternalVariables);

    return input;
}

OBJECT_CLASS(FmuInput, ComponentInput);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */