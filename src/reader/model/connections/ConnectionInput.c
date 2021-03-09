/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/connections/ConnectionInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ConnectionInputDestructor(ConnectionInput * input) {
    if (input->from.scalarEndpoint) { object_destroy(input->from.scalarEndpoint); }
    if (input->to.scalarEndpoint) { object_destroy(input->to.scalarEndpoint); }
    if (input->interExtrapolation) { object_destroy(input->interExtrapolation); }
    if (input->decoupleSettings) { object_destroy(input->decoupleSettings); }
}

static ConnectionInput * ConnectionInputCreate(ConnectionInput * input) {
    input->fromType = ENDPOINT_SCALAR;
    input->from.scalarEndpoint = NULL;

    input->toType = ENDPOINT_SCALAR;
    input->to.scalarEndpoint = NULL;

    OPTIONAL_UNSET(input->interExtrapolationType);
    input->interExtrapolation = NULL;

    OPTIONAL_UNSET(input->decoupleType);
    input->decoupleSettings = NULL;

    return input;
}

OBJECT_CLASS(ConnectionInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */