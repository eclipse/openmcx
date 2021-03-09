/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/ssp/Reader.h"

#include "reader/ssp/Config.h"
#include "reader/ssp/Schema.h"
#include "reader/ssp/Task.h"
#include "reader/ssp/Model.h"
#include "reader/ssp/Units.h"
#include "reader/ssp/Util.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


static xmlDocPtr _doc = NULL;


McxStatus SSDReaderInit(const char * file) {
    xml_configure_path_resolution(file);
    xml_init_parser();
    xml_set_error_handlers();

    // TODO: replace memory functions if needed (see `xmlMemSetup`)
    return RETURN_OK;
}


void SSDReaderCleanup() {
    xml_cleanup_parsed_schemas();
    xml_cleanup_path_resolution_configuration();

    if (_doc) {
        xml_free_doc(_doc);
        _doc = NULL;
    }
}


InputRoot * SSDReadMcx(const char * file, SSDComponentSpecificDataDefinition * components[]) {
    InputRoot * input = (InputRoot *) object_create(InputRoot);
    InputElement * element = (InputElement *) input;
    ObjectContainer * units = NULL;

    McxStatus retVal = RETURN_OK;

    if (!input) {
        return NULL;
    }

    if (_doc) {
        mcx_log(LOG_ERROR, "Trying to parse multiple files with the same parser instance");
        retVal = RETURN_ERROR;
        goto cleanup;
    }

    _doc = xml_read_doc(file);
    if (!_doc) {
        mcx_log(LOG_ERROR, "Could not parse ssd file: %s", file);
        retVal = RETURN_ERROR;
        goto cleanup;
    }

    retVal = xml_validate_doc(_doc, "SystemStructureDescription.xsd");
    if (retVal == RETURN_ERROR) {
        goto cleanup;
    }

    xmlNodePtr root_node = xml_root(_doc);

    element->type = INPUT_SSD;
    element->context = (void*)root_node;

    {
        // read task and result data
        xmlNodePtr default_experiment_node = xml_child(root_node, "DefaultExperiment");

        input->task = SSDReadTask(default_experiment_node);
        if (!input->task) {
            retVal = RETURN_ERROR;
            goto cleanup;
        }
    }

    {
        // read config
        xmlNodePtr system_node = xml_child(root_node, "System");
        xmlNodePtr elements_node = xml_child(system_node, "Elements");

        xmlNodePtr annotation_node = NULL;
        xmlNodePtr default_experiment_node = xml_child(root_node, "DefaultExperiment");
        if (default_experiment_node) {
            annotation_node = xml_annotation_of_type(default_experiment_node, "com.avl.model.connect.ssp.config");
        }


        input->config = SSDReadConfig(annotation_node, elements_node);
        if (!input->config) {
            retVal = RETURN_ERROR;
            goto cleanup;
        }
    }

    {
        // read units
        units = SSDReadUnits(xml_child(root_node, "Units"));
        if (!units) {
            retVal = RETURN_ERROR;
            goto cleanup;
        }
    }

    {
        // read model with components and connections
        xmlNodePtr system_node = xml_child(root_node, "System");

        input->model = SSDReadModel(system_node, components, units);
        if (!input->model) {
            retVal = RETURN_ERROR;
            goto cleanup;
        }
    }

cleanup:
    if (units) {
        units->DestroyObjects(units);
        object_destroy(units);
    }

    if (retVal == RETURN_ERROR) {
        object_destroy(input);
        return NULL;
    }

    return input;
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */