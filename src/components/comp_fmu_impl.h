/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_COMPONENTS_COMP_FMU_IMPL_H
#define MCX_COMPONENTS_COMP_FMU_IMPL_H

#include "components/comp_fmu.h"
#include "fmu/common_fmu1.h"
#include "fmu/common_fmu2.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct CompFMU {
    Component _;

    FmuCommon common;

    Fmu1CommonStruct fmu1;
    Fmu2CommonStruct fmu2;
    int localValues;

    double lastCommunicationTimePoint;
} CompFMU;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif  // MCX_COMPONENTS_COMP_FMU_IMPL_H