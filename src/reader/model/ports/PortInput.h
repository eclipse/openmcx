/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_MODEL_PORTS_PORT_INPUT_H
#define MCX_READER_MODEL_PORTS_PORT_INPUT_H

#include "reader/core/InputElement.h"
#include "reader/model/ports/VectorPortInput.h"
#include "reader/model/ports/ScalarPortInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct PortInput PortInput;

typedef McxStatus (*fPortInputCopyFrom)(PortInput * self, PortInput * src);

extern const ObjectClass _PortInput;

typedef enum PortInputType {
    PORT_VECTOR,
    PORT_SCALAR
} PortInputType;

typedef union PortInputPort {
    VectorPortInput * vectorPort;
    ScalarPortInput * scalarPort;
} PortInputPort;

struct PortInput {
    InputElement _;

    PortInputType type;
    PortInputPort port;

    fPortInputCopyFrom CopyFrom;
};

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_MODEL_PORTS_PORT_INPUT_H