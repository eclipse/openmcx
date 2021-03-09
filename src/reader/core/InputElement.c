/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/core/InputElement.h"
#include <stdarg.h>

#include "reader/ssp/Util.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static InputElement * Clone(InputElement * self) {
    InputElement * clone = (InputElement *)object_create(InputElement);
    McxStatus retVal = RETURN_ERROR;

    if (!clone) {
        return NULL;
    }

    retVal = clone->CopyFrom(clone, self);

    // cleanup:
    if (retVal == RETURN_ERROR) {
        object_destroy(clone);
        return NULL;
    }

    return clone;
}

static McxStatus CopyFrom(InputElement * self, InputElement * src) {
    if (!self || !src) {
        mcx_log(LOG_ERROR, "InputElement: Invalid copy arguments");
        return RETURN_ERROR;
    }

    self->type = src->type;
    self->context = src->context;       // no deep copy because of void *

    return RETURN_OK;
}

static void InputElementDestructor(InputElement * input) {
}

static InputElement * InputElementCreate(InputElement * input) {
    input->type = INPUT_UNSPECIFIED;
    input->context = NULL;

    input->Clone = Clone;
    input->CopyFrom = CopyFrom;

    return input;
}

OBJECT_CLASS(InputElement, Object);

McxStatus input_element_error(InputElement * element, const char * format, ...) {
#define MSG_MAX_SIZE 2048
    char msg[MSG_MAX_SIZE] = { 0 };
    va_list args;

    va_start(args, format);
    vsnprintf(msg, MSG_MAX_SIZE, format, args);
    va_end(args);

    if (element->type == INPUT_SSD) {
        xmlNodePtr node = (xmlNodePtr)element->context;
        mcx_log(LOG_ERROR, "In input file, node %s at line %lu: %s",
                xml_node_get_name(node), xml_node_line_number(node), msg);
    }
    else {
        mcx_log(LOG_ERROR, msg);
    }

    return RETURN_ERROR;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */