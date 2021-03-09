/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_CORE_TASK_H
#define MCX_CORE_TASK_H

#include "core/Config.h"
#include "steptypes/StepType.h" /* for StepTypeType */
#include "reader/task/TaskInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct Task Task;

struct Config;
struct Model;
struct ResultsStorage;
struct StepType;
struct StepTypeParams;

typedef enum StoreLevel StoreLevel;
typedef enum StepTypeType StepTypeType;

/* generic function definitions */
typedef McxStatus (* fTaskSetup)(Task * task, struct Model * model);
typedef McxStatus (* fTaskRead)(Task * task, TaskInput * node);
typedef McxStatus (* fTaskRun)(Task * task, struct Model * model);

typedef void (* fTaskSetConfig)(Task * task, struct Config * config);
typedef StepTypeType (* fTaskGetStepTypeType)(Task * task);

typedef double (* fTaskGetTimeStep)(Task * task);

extern const struct ObjectClass _Task;

struct Task {
    Object _; // super class first

    fTaskRead Read;
    fTaskSetup Setup;
    fTaskRun PrepareRun;
    fTaskRun Run;

    fTaskSetConfig SetConfig;
    fTaskGetStepTypeType GetStepTypeType;

    fTaskGetTimeStep GetTimeStep;

    const Config * config;
    struct ResultsStorage * storage;

    // parameters
    double timeStart;
    double timeEnd;
    int timeEndDefined;
    int stopIfFirstComponentFinished;

    int useInputsAtEndTime;
    int storeInputsAtEndTime;

    double relativeEps;

    int rtFactorEnabled;

    // working variables
    struct StepTypeParams * params;
    StepTypeType stepTypeType;
    struct StepType * stepType;

    FinishState finishState;

    StoreLevel storeLevel;

};

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_CORE_TASK_H */