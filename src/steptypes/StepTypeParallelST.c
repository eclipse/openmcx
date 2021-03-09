/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "core/SubModel.h"
#include "steptypes/StepTypeParallelST.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


static McxStatus ParallelSTDoStep(StepType * stepType, StepTypeParams * params, SubModel * subModel) {
    McxStatus retVal = RETURN_OK;

    retVal = subModel->LoopComponents(subModel, CompEnterCouplingStepMode, (void *) params);
    if (RETURN_OK != retVal) {
        mcx_log(LOG_ERROR, "Simulation: Enter coupling step mode of elements failed");
        return RETURN_ERROR;
    }

    // pre do update: parts of do-step that must not be multi-threaded
    retVal = subModel->LoopComponents(subModel, CompPreDoUpdateState, (void *) params);
    if (RETURN_OK != retVal) {
        mcx_log(LOG_ERROR, "Simulation: Pre do update of elements failed");
        return RETURN_ERROR;
    }

    retVal = subModel->LoopEvaluationList(subModel, CompDoStep, (void *) params);
    if (RETURN_ERROR == retVal) {
        mcx_log(LOG_ERROR, "Simulation: Do step of elements failed");
        return RETURN_ERROR;
    }
    retVal = subModel->LoopEvaluationList(subModel, CompEnterCommunicationPoint, (void *) params);
    if (RETURN_ERROR == retVal) {
        mcx_log(LOG_ERROR, "Simulation: Enter communication point of elements failed");
        return RETURN_ERROR;
    }

    return RETURN_OK;
}

static void StepTypeParallelSTDestructor(StepTypeParallelST * parallelType) {
}

static StepTypeParallelST * StepTypeParallelSTCreate(StepTypeParallelST * parallelType) {
    StepType * type = (StepType *) parallelType;

    type->DoStep = ParallelSTDoStep;

    type->type = STEP_TYPE_PARALLEL_ST;

    return parallelType;
}

OBJECT_CLASS(StepTypeParallelST, StepType);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */