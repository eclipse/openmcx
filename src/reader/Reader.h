/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_READER_READER_H
#define MCX_READER_READER_H

#include "CentralParts.h"

#include "core/Config.h"

#include "reader/InputRoot.h"

#include "reader/ssp/Reader.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
    FILE_FORMAT_UNKNOWN,
    FILE_FORMAT_SSD
} FileFormat;

extern const ObjectClass _Reader;

typedef struct Reader Reader;

typedef McxStatus (*fReaderSetup)(Reader * reader, const char * modelFile, Config * config);
typedef void (*fReaderCleanup)(Reader * reader);
typedef InputRoot * (*fReaderRead)(Reader * reader, const char * file);

typedef SSDComponentSpecificDataDefinition ** (*fReaderGetSSDComponents)(Reader * reader);

struct Reader {
    Object _;

    fReaderSetup Setup;
    fReaderCleanup Cleanup;
    fReaderRead Read;

    fReaderGetSSDComponents GetSSDComponents_;

    int reader_initialised_;
    FileFormat format_;
};

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //  MCX_READER_READER_H