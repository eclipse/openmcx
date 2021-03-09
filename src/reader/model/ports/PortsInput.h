/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_MODEL_PORTS_PORTS_INPUT_H
#define MCX_READER_MODEL_PORTS_PORTS_INPUT_H

#include "reader/core/InputElement.h"
#include "reader/model/ports/PortInput.h"   // included for convenience

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct PortsInput PortsInput;

typedef McxStatus (*fPortsInputCopyFrom)(PortsInput * self, PortsInput * src);

extern const ObjectClass _PortsInput;

struct PortsInput {
    InputElement _;

    ObjectContainer * ports;

    fPortsInputCopyFrom CopyFrom;
};

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_MODEL_PORTS_PORTS_INPUT_H