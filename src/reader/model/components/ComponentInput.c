/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/model/components/ComponentInput.h"

#include "util/string.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static InputElement * Clone(InputElement * self) {
    ComponentInput * clone = (ComponentInput *)object_create(ComponentInput);
    McxStatus retVal = RETURN_ERROR;

    if (!clone) {
        return NULL;
    }

    retVal = clone->CopyFrom(clone, (ComponentInput *) self);

    // cleanup:
    if (retVal == RETURN_ERROR) {
        object_destroy(clone);
        return NULL;
    }

    return (InputElement *) clone;
}

static McxStatus CopyFrom(ComponentInput * self, ComponentInput * src) {
    InputElement * base = (InputElement *)self;
    McxStatus retVal = RETURN_OK;

    if (!self || !src) {
        mcx_log(LOG_ERROR, "ComponentInput: Invalid copy arguments");
        return RETURN_ERROR;
    }

    // copy base class first
    retVal = base->CopyFrom(base, (InputElement *)src);
    if (retVal == RETURN_ERROR) {
        return RETURN_ERROR;
    }

    // copy src members
    self->type = object_strong_reference(src->type);
    self->name = mcx_string_copy(src->name);
    if (!self->name && src->name) {
        return RETURN_ERROR;
    }
    self->triggerSequence = src->triggerSequence;
    self->inputAtEndTime = src->inputAtEndTime;
    if (src->inports) {
        InputElement * srcPorts = (InputElement *)src->inports;
        self->inports = (PortsInput *)srcPorts->Clone(srcPorts);
        if (!self->inports) {
            mcx_log(LOG_ERROR, "Copying input ports data failed");
            return RETURN_ERROR;
        }
    }

    if (src->outports) {
        InputElement * srcPorts = (InputElement *)src->outports;
        self->outports = (PortsInput *)srcPorts->Clone(srcPorts);
        if (!self->outports) {
            mcx_log(LOG_ERROR, "Copying output ports data failed");
            return RETURN_ERROR;
        }
    }

    if (src->results) {
        InputElement * srcResults = (InputElement *)src->results;
        self->results = (ComponentResultsInput *)srcResults->Clone(srcResults);
        if (!self->results) {
            mcx_log(LOG_ERROR, "Copying results data failed");
            return RETURN_ERROR;
        }
    }

    return RETURN_OK;
}

static void ComponentInputDestructor(ComponentInput * input) {
    if (input->name) { mcx_free(input->name); }

    if (input->type) { object_destroy(input->type); }
    if (input->inports) { object_destroy(input->inports); }
    if (input->outports) { object_destroy(input->outports); }
    if (input->parameters) { object_destroy(input->parameters); }
    if (input->initialValues) { object_destroy(input->initialValues); }
    if (input->results) { object_destroy(input->results); }

}

static ComponentInput * ComponentInputCreate(ComponentInput * input) {
    InputElement * base = (InputElement *)input;

    input->type = NULL;
    input->name = NULL;
    OPTIONAL_UNSET(input->triggerSequence);
    OPTIONAL_UNSET(input->inputAtEndTime);
    OPTIONAL_UNSET(input->deltaTime);

    input->inports = NULL;
    input->outports = NULL;

    input->parameters = NULL;
    input->initialValues = NULL;

    input->results = NULL;

    base->Clone = Clone;
    input->CopyFrom = CopyFrom;

    return input;
}

OBJECT_CLASS(ComponentInput, InputElement);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */