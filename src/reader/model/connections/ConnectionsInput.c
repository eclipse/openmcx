/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/connections/ConnectionsInput.h"

#include "objects/ObjectContainer.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ConnectionsInputDestructor(ConnectionsInput * input) {
    if (input->connections) {
        input->connections->DestroyObjects(input->connections);
        object_destroy(input->connections);
    }
}

static ConnectionsInput * ConnectionsInputCreate(ConnectionsInput * input) {
    input->connections = object_create(ObjectContainer);

    if (!input->connections) {
        return NULL;
    }

    return input;
}

OBJECT_CLASS(ConnectionsInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */