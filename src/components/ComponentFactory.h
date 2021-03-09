/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_COMPONENTS_COMPONENTFACTORY_H
#define MCX_COMPONENTS_COMPONENTFACTORY_H

#include "CentralParts.h"
#include "ComponentTypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct ComponentFactory;
typedef struct ComponentFactory ComponentFactory;

typedef struct Component Component;

typedef Component * (* fComponentFactoryCreateComponent)(ComponentFactory * factory, ComponentType * type, size_t id);


extern const struct ObjectClass _ComponentFactory;

struct ComponentFactory {
    Object _;

    fComponentFactoryCreateComponent CreateComponent;

    // private method
    fComponentFactoryCreateComponent _CreateComponent;
};


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_COMPONENTS_COMPONENTFACTORY_H */