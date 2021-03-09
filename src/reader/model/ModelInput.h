/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_MODEL_MODEL_INPUT_H
#define MCX_READER_MODEL_MODEL_INPUT_H

#include "reader/core/InputElement.h"
#include "reader/model/components/ComponentsInput.h"
#include "reader/model/connections/ConnectionsInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern const ObjectClass _ModelInput;

typedef struct ModelInput {
    InputElement _;

    ComponentsInput * components;
    ConnectionsInput * connections;

} ModelInput;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_MODEL_MODEL_INPUT_H