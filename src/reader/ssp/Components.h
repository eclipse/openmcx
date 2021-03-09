/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_SSP_COMPONENTS_H
#define MCX_READER_SSP_COMPONENTS_H

#include "reader/model/components/ComponentInput.h"
#include "reader/model/components/ComponentsInput.h"
#include "reader/ssp/Ports.h"
#include "reader/ssp/Parameters.h"

#include "reader/ssp/Util.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
    SSD_IMPLEMENTATION_COSIM,
    SSD_IMPLEMENTATION_ME,
    SSD_IMPLEMENTATION_ANY
} SSDImplementation;

typedef McxStatus (*fReadSSDComponentSpecificData)(xmlNodePtr componentNode, xmlNodePtr annotationNode, ComponentInput * compInput);
typedef McxStatus (*fDefaultSSDComponentSpecificData)(xmlNodePtr componentNode, ComponentInput * compInput);

typedef struct {
    const char * mimeType;
    const char * annotationType;
    const ObjectClass * compType;
    const ObjectClass * inputType;
    fReadSSDComponentSpecificData Read;
    fDefaultSSDComponentSpecificData DefaultSpecificData;
    const ObjectClass * portType;
    const char * portAnnotationType;
    fReadSSDPortSpecificData ReadPort;
    fSSDParameterSetter SetParameters;
    const ObjectClass * parameterType;
    const char * parameterAnnotationType;
    fReadSSDParameterSpecificData ReadParameter;
    fSSDParameterSpecificDataDefault DefaultParameter;
} SSDComponentSpecificDataDefinition;

extern SSDComponentSpecificDataDefinition ssdCommonSpecificDataDefinition[];
extern SSDComponentSpecificDataDefinition * ssdMcxExeComponents[];

ComponentsInput * SSDReadComponents(xmlNodePtr componentsNode,
                                    SSDComponentSpecificDataDefinition * components[],
                                    int processSubsystems,
                                    SSDImplementation supportedImplementation,
                                    ObjectContainer * units);


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */


#endif // !MCX_READER_SSP_COMPONENTS_H