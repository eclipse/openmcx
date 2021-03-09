/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/task/TaskInput.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void TaskInputDestructor(TaskInput * input) {
    if (input->results) { object_destroy(input->results); }
}

static TaskInput * TaskInputCreate(TaskInput * input) {
    OPTIONAL_UNSET(input->startTime);
    OPTIONAL_UNSET(input->endTime);
    OPTIONAL_UNSET(input->deltaTime);

    OPTIONAL_UNSET(input->sumTime);
    OPTIONAL_UNSET(input->inputAtEndTime);

    OPTIONAL_UNSET(input->endType);

    OPTIONAL_UNSET(input->relativeEps);

    OPTIONAL_UNSET(input->timingOutput);

    input->stepType = STEP_TYPE_UNDEFINED;

    input->results = NULL;

    return input;
}

OBJECT_CLASS(TaskInput, InputElement);


TaskInput * CreateDefaultTaskInput(InputType type) {
    TaskInput * input = (TaskInput*)object_create(TaskInput);
    InputElement * element = (InputElement*)input;

    if (!input) {
        return NULL;
    }

    element->type = type;
    element->context = NULL;

    input->stepType = STEP_TYPE_PARALLEL_MT;

    return input;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */