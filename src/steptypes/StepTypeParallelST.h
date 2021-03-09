/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_STEPTYPES_STEP_TYPE_PARALLEL_ST_H
#define MCX_STEPTYPES_STEP_TYPE_PARALLEL_ST_H

#include "steptypes/StepType.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern const struct ObjectClass _StepTypeParallelST;

typedef struct StepTypeParallelST {
    StepType _;

} StepTypeParallelST;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_STEPTYPES_STEP_TYPE_PARALLEL_ST_H */