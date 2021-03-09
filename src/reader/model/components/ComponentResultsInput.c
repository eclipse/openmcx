/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/components/ComponentResultsInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static InputElement * Clone(InputElement * self) {
    ComponentResultsInput * clone = (ComponentResultsInput *)object_create(ComponentResultsInput);
    McxStatus retVal = RETURN_ERROR;

    if (!clone) {
        return NULL;
    }

    retVal = clone->CopyFrom(clone, (ComponentResultsInput *) self);

    // cleanup:
    if (retVal == RETURN_ERROR) {
        object_destroy(clone);
        return NULL;
    }

    return (InputElement *) clone;
}

static McxStatus CopyFrom(ComponentResultsInput * self, ComponentResultsInput * src) {
    InputElement * base = (InputElement *)self;
    size_t i = 0;
    McxStatus retVal = RETURN_OK;

    if (!self || !src) {
        mcx_log(LOG_ERROR, "ComponentResultsInput: Invalid copy arguments");
        return RETURN_ERROR;
    }

    // copy base class first
    retVal = base->CopyFrom(base, (InputElement *)src);
    if (retVal == RETURN_ERROR) {
        return RETURN_ERROR;
    }

    // copy src members
    self->rtFactor = src->rtFactor;
    self->resultLevel = src->resultLevel;
    self->startTime = src->startTime;
    self->endTime = src->endTime;
    self->stepTime = src->stepTime;
    self->stepCount = src->stepCount;

    return RETURN_OK;
}

static void ComponentResultsInputDestructor(ComponentResultsInput * input) {
}

static ComponentResultsInput * ComponentResultsInputCreate(ComponentResultsInput * input) {
    InputElement * inputElement = (InputElement *)input;

    OPTIONAL_UNSET(input->rtFactor);
    OPTIONAL_UNSET(input->resultLevel);

    OPTIONAL_UNSET(input->startTime);
    OPTIONAL_UNSET(input->endTime);
    OPTIONAL_UNSET(input->stepTime);
    OPTIONAL_UNSET(input->stepCount);

    inputElement->Clone = Clone;
    input->CopyFrom = CopyFrom;

    return input;
}

OBJECT_CLASS(ComponentResultsInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */