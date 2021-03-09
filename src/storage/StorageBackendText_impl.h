/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "CentralParts.h"

#if defined (ENABLE_STORAGE)
#include "storage/ResultsStorage.h"
#include "storage/ComponentStorage.h"
#include "storage/ChannelStorage.h"

#include "storage/StorageBackendText.h"

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SIZE 2048

typedef struct TextFile {
    char * name;
    FILE * fp;
} TextFile;

typedef struct TextComponent {
    TextFile files[CHANNEL_STORE_NUM];
} TextComponent;

typedef struct StorageBackendText {
    StorageBackend _;

    fStorageBackendSetup WritePPDFile;
    fStorageBackendSetup SetupComponentFiles;

    size_t numComponents;
    TextComponent * comps;

    char * path;

    int flushEveryStore;

    const char * separator;

} StorageBackendText;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //ENABLE_STORAGE
