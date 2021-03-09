/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/components/ComponentsInput.h"

#include "objects/ObjectContainer.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void ComponentsInputDestructor(ComponentsInput * input) {
    if (input->components) {
        input->components->DestroyObjects(input->components);
        object_destroy(input->components);
    }
}

static ComponentsInput * ComponentsInputCreate(ComponentsInput * input) {
    input->components = (ObjectContainer *) object_create(ObjectContainer);

    if (!input->components) {
        return NULL;
    }

    return input;
}

OBJECT_CLASS(ComponentsInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */