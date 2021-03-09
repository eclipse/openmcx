/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_SSP_UNITS_H
#define MCX_READER_SSP_UNITS_H

#include "objects/Object.h"
#include "objects/ObjectContainer.h"

#include "units/Units.h"

#include "reader/ssp/Util.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


extern const ObjectClass _SSDUnit;

typedef struct SSDUnit SSDUnit;

typedef SSDUnit*(*fSSDUnitClone)(SSDUnit * unit);


struct SSDUnit {
    Object _;

    fSSDUnitClone Clone;

    char * name;
    si_def siDefinition;
};


ObjectContainer * SSDReadUnits(xmlNodePtr unitsNode);


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */


#endif // !MCX_READER_SSP_UNITS_H