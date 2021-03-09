/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_SSP_SCHEMA_H
#define MCX_READER_SSP_SCHEMA_H

#include <libxml/tree.h>

#include "CentralParts.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


McxStatus xml_validate_node(xmlNodePtr node, const char * schema_id);
McxStatus xml_validate_doc(xmlDocPtr doc, const char * schema_id);

void xml_cleanup_parsed_schemas();


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */


#endif // !MCX_READER_SSP_SCHEMA_H