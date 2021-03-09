/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_MODEL_CONNECTIONS_CONNECTION_INPUT_H
#define MCX_READER_MODEL_CONNECTIONS_CONNECTION_INPUT_H

#include "reader/core/InputElement.h"
#include "reader/model/connections/EndpointInput.h"
#include "reader/model/connections/InterExtrapolationInput.h"
#include "reader/model/connections/DecoupleInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

MAKE_OPTIONAL_TYPE(InterExtrapolationType);
MAKE_OPTIONAL_TYPE(DecoupleType);

typedef enum EndpointInputType {
    ENDPOINT_SCALAR,
    ENDPOINT_VECTOR
} EndpointInputType;

typedef union EndpointInput {
    ScalarEndpointInput * scalarEndpoint;
    VectorEndpointInput * vectorEndpoint;
} EndpointInput;

extern const ObjectClass _ConnectionInput;

typedef struct ConnectionInput {
    InputElement _;

    EndpointInputType fromType;
    EndpointInput from;

    EndpointInputType toType;
    EndpointInput to;

    OPTIONAL_VALUE(InterExtrapolationType) interExtrapolationType;
    InterExtrapolationInput * interExtrapolation;

    OPTIONAL_VALUE(DecoupleType) decoupleType;
    InputElement * decoupleSettings;
} ConnectionInput;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_MODEL_CONNECTIONS_CONNECTION_INPUT_H