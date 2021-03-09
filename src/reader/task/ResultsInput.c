/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/task/ResultsInput.h"

#include "util/string.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ResultsInputDestructor(ResultsInput * input) {
    if (input->outputDirectory) { mcx_free(input->outputDirectory); }
    if (input->backends) { object_destroy(input->backends); }
}

static ResultsInput * ResultsInputCreate(ResultsInput * input) {
    input->outputDirectory = NULL;

    OPTIONAL_UNSET(input->resultLevel);

    input->backends = NULL;

    return input;
}

OBJECT_CLASS(ResultsInput, InputElement);


ResultsInput * CreateDefaultResultsInput(InputType type) {
    ResultsInput * input = (ResultsInput*)object_create(ResultsInput);
    InputElement * element = (InputElement*)input;
    BackendInput * csvBackend = NULL;

    if (!input) {
        return NULL;
    }

    element->type = type;
    element->context = NULL;

    input->outputDirectory = mcx_string_copy("results");
    OPTIONAL_SET(input->resultLevel, STORE_SYNCHRONIZATION);

    // Use CSV as a default backend
    input->backends = (BackendsInput*)object_create(BackendsInput);
    if (!input->backends) {
        goto cleanup;
    }

    csvBackend = (BackendInput*)object_create(BackendInput);
    if (!csvBackend) {
        goto cleanup;
    }

    OPTIONAL_SET(csvBackend->storeAtRuntime, TRUE);
    csvBackend->type = BACKEND_CSV;

    if (input->backends->backends->PushBack(input->backends->backends, (Object *)csvBackend) == RETURN_ERROR) {
        goto cleanup;
    }

    return input;

cleanup:
    object_destroy(input);
    object_destroy(csvBackend);
    return NULL;
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */