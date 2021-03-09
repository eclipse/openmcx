/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/ssp/Config.h"
#include "reader/ssp/Schema.h"
#include "util/paths.h"
#include "util/os.h"
#include "units/Units.h"

#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


ConfigInput * SSDReadConfig(xmlNodePtr annotationNode, xmlNodePtr elementsNode) {
    ConfigInput * configInput = (ConfigInput*)object_create(ConfigInput);
    InputElement * element = (InputElement *)configInput;

    McxStatus retVal = RETURN_OK;

    if (!configInput) {
        return NULL;
    }

    element->type = INPUT_SSD;

    if (annotationNode) {
        xmlNodePtr configNode = xml_child(annotationNode, "Config");

        element->context = (void*)configNode;

        if (!configNode) {
            retVal = xml_error_missing_child(annotationNode, "Config");
            goto cleanup;
        }

        retVal = xml_validate_node(configNode, "com.avl.model.connect.ssp.config");
        if (retVal == RETURN_ERROR) {
            goto cleanup;
        }

    }

cleanup:
    if (retVal == RETURN_ERROR) {
        object_destroy(configInput);
        return NULL;
    }

    return configInput;
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */