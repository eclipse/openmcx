/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_CORE_CONNECTIONS_FILTERS_EXT_FILTER_H
#define MCX_CORE_CONNECTIONS_FILTERS_EXT_FILTER_H

#include "core/connections/filters/Filter.h"

#include "core/Interpolation.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct ExtFilter ExtFilter;

typedef McxStatus (* fExtFilterSetup)(ExtFilter * filter, int degree);

extern const struct ObjectClass _ExtFilter;

struct ExtFilter {
    ChannelFilter _;

    fExtFilterSetup Setup;

    double value;
    int degree;

    mcx_table_poly * polyStruct;
    int n;  // number of samples

    double lastRealCouplingStepTime;
    double lastRealCouplingStepValue;
};


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_CORE_CONNECTIONS_FILTERS_EXT_FILTER_H */