/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/InputRoot.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void InputRootDestructor(InputRoot * input) {
    if (input->config) { object_destroy(input->config); }
    if (input->model) { object_destroy(input->model); }
    if (input->task) { object_destroy(input->task); }
}

static InputRoot * InputRootCreate(InputRoot * input) {
    input->config = NULL;
    input->model = NULL;
    input->task = NULL;

    return input;
}

OBJECT_CLASS(InputRoot, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */