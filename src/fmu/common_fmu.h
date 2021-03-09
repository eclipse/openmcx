/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_FMU_COMMON_FMU_H
#define MCX_FMU_COMMON_FMU_H

#include "CentralParts.h"
#include "reader/model/components/specific_data/FmuInput.h"
#include "core/Config.h"

#include "fmilib.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void * JMCallbackMalloc(size_t size);
void * JMCallbackCalloc(size_t num, size_t size);
void * JMCallbackRealloc(void * ptr, size_t size);
void   JMCallbackFree(void * ptr);
void   JMCallbackLogger(jm_callbacks* c, jm_string module, jm_log_level_enu_t log_level, jm_string message);

jm_callbacks * JMGetCallbacks(void);

typedef struct FmuCommon {
    fmi_version_enu_t version;
    jm_callbacks callbacks;
    fmi_import_context_t * context;

    char * instanceName;
    char * fmuFile;
    char * path;

    int isLocal;
} FmuCommon;


void FmuCommonInit(FmuCommon * fmu);

McxStatus FmuCommonRead(FmuCommon * common, FmuInput * input);
McxStatus FmuCommonSetup(FmuCommon * fmu);

McxStatus FmuOpen(FmuCommon * fmu, const struct Config * const config);

McxStatus CreateFmuExtractPath(FmuCommon * fmu, const char * name, const Config * config);

void FmuCommonDestructor(FmuCommon * fmu);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_FMU_COMMON_FMU_H */