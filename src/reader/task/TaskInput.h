/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_TASK_TASK_INPUT_H
#define MCX_READER_TASK_TASK_INPUT_H

#include "steptypes/StepType.h"

#include "reader/core/InputElement.h"
#include "reader/task/ResultsInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum TaskEndType {
    END_TYPE_TIME,
    END_TYPE_FIRST_COMPONENT
} TaskEndType;

MAKE_OPTIONAL_TYPE(TaskEndType);

extern const ObjectClass _TaskInput;

typedef struct TaskInput {
    InputElement _;

    OPTIONAL_VALUE(double) startTime;           // task start time in seconds
    OPTIONAL_VALUE(double) endTime;             // task end time in seconds
    OPTIONAL_VALUE(double) deltaTime;           // task time step in seconds

    OPTIONAL_VALUE(int) sumTime;                // flag for task time (whether to use summation or not)
    OPTIONAL_VALUE(int) inputAtEndTime;         // task input evalutation time

    OPTIONAL_VALUE(double) relativeEps;         // relative epsilon value

    OPTIONAL_VALUE(int) timingOutput;           // on/off flag for RT factor calculation

    OPTIONAL_VALUE(TaskEndType) endType;        // task stop condition

    StepTypeType stepType;                      // step type used for the task

    ResultsInput * results;
} TaskInput;

TaskInput * CreateDefaultTaskInput(InputType type);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_TASK_TASK_INPUT_H