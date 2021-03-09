/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/ssp/Model.h"
#include "reader/ssp/Components.h"
#include "reader/ssp/Connections.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


ModelInput * SSDReadModel(xmlNodePtr systemNode, SSDComponentSpecificDataDefinition * components[], ObjectContainer * units) {
    ModelInput * modelInput = (ModelInput *) object_create(ModelInput);
    InputElement * element = (InputElement *) modelInput;

    McxStatus retVal = RETURN_OK;

    if (!modelInput) {
        return NULL;
    }

    element->type = INPUT_SSD;
    element->context = (void *) systemNode;

    {
        xmlNodePtr elementsNode = xml_child(systemNode, "Elements");

        if (elementsNode) {
            modelInput->components = SSDReadComponents(elementsNode, components, TRUE, SSD_IMPLEMENTATION_COSIM, units);
            if (!modelInput->components) {
                retVal = RETURN_ERROR;
                goto cleanup;
            }
        } else {
            modelInput->components = (ComponentsInput *) object_create(ComponentsInput);
            if (!modelInput->components) {
                retVal = RETURN_ERROR;
                goto cleanup;
            }
        }
    }

    {
        xmlNodePtr connectionsNode = xml_child(systemNode, "Connections");

        if (connectionsNode) {
            modelInput->connections = SSDReadConnections(connectionsNode);
            if (!modelInput->connections) {
                retVal = RETURN_ERROR;
                goto cleanup;
            }
        } else {
            modelInput->connections = (ConnectionsInput *) object_create(ConnectionsInput);
            if (!modelInput->connections) {
                retVal = RETURN_ERROR;
                goto cleanup;
            }
        }
    }

cleanup:
    if (retVal == RETURN_ERROR) {
        object_destroy(modelInput);
        return NULL;
    }

    return modelInput;
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */