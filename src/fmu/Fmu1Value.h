/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_FMU_FMU1VALUE_H
#define MCX_FMU_FMU1VALUE_H

#include "CentralParts.h"
#include "core/channels/Channel.h"
#include "fmilib.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct Fmu1Value;

typedef struct Fmu1Value Fmu1Value;

typedef McxStatus(*fFmu1ValueSetFromChannelValue)(Fmu1Value * v, ChannelValue * val);

extern const struct ObjectClass _Fmu1Value;

struct Fmu1Value {
    Object _; /* base class */

    fFmu1ValueSetFromChannelValue SetFromChannelValue;

    char * name;

    Channel * channel;
    fmi1_value_reference_t vr;
    fmi1_import_variable_t * var;
    ChannelValue val;
};

Fmu1Value * Fmu1ValueMake(const char * name, fmi1_import_variable_t * var, Channel * channel);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_FMU_FMU1VALUE_H */