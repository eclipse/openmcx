/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_TASK_RESULTS_INPUT_H
#define MCX_READER_TASK_RESULTS_INPUT_H

#include "reader/core/InputElement.h"
#include "reader/task/BackendsInput.h"
#include "reader/task/BackendInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern const ObjectClass _ResultsInput;

typedef struct ResultsInput {
    InputElement _;

    char * outputDirectory;

    OPTIONAL_VALUE(StoreLevel) resultLevel;

    BackendsInput * backends;
} ResultsInput;

ResultsInput * CreateDefaultResultsInput(InputType type);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_TASK_RESULTS_INPUT_H