/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/ports/PortInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static InputElement * Clone(InputElement * self) {
    PortInput * clone = (PortInput *)object_create(PortInput);
    McxStatus retVal = RETURN_ERROR;

    if (!clone) {
        return NULL;
    }

    retVal = clone->CopyFrom(clone, (PortInput *) self);

    // cleanup:
    if (retVal == RETURN_ERROR) {
        object_destroy(clone);
        return NULL;
    }

    return (InputElement*) clone;
}

static McxStatus CopyFrom(PortInput * self, PortInput * src) {
    InputElement * base = (InputElement *)self;
    McxStatus retVal = RETURN_OK;

    if (!self || !src) {
        mcx_log(LOG_ERROR, "PortInput: Invalid copy arguments");
        return RETURN_ERROR;
    }

    // copy base class first
    retVal = base->CopyFrom(base, (InputElement *)src);
    if (retVal == RETURN_ERROR) {
        return RETURN_ERROR;
    }

    // copy src members
    self->type = src->type;

    if (self->type == PORT_VECTOR) {
        InputElement * srcPort = (InputElement *)src->port.vectorPort;
        self->port.vectorPort = (VectorPortInput *)srcPort->Clone(srcPort);
    } else {
        InputElement * srcPort = (InputElement *)src->port.scalarPort;
        self->port.scalarPort = (ScalarPortInput *)srcPort->Clone(srcPort);
    }

    if (!self->port.scalarPort && src->port.scalarPort) {
        mcx_log(LOG_ERROR, "Cloning port data failed");
        return RETURN_ERROR;
    }

    return RETURN_OK;
}

static void PortInputDestructor(PortInput * input) {
    if (input->port.vectorPort) { object_destroy(input->port.vectorPort); }
}

static PortInput * PortInputCreate(PortInput * input) {
    InputElement * inputElement = (InputElement *)input;

    input->type = PORT_VECTOR;
    input->port.vectorPort = NULL;

    inputElement->Clone = Clone;
    input->CopyFrom = CopyFrom;

    return input;
}

OBJECT_CLASS(PortInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */