/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>

#include "common/memory.h"

#include "util/paths.h"
#include "util/string.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

char * mcx_path_get_absolute(const char * path) {
    DWORD retVal = 0;
    DWORD len = 4096;
    wchar_t * wPath = NULL;
    wchar_t * wAbsPath = NULL;

    if (NULL == path) {
        return NULL;
    }

    if (mcx_path_is_absolute(path)) {
        return mcx_string_copy(path);
    }

    wPath = mcx_string_to_widechar(path);
    wAbsPath = (wchar_t *) mcx_malloc(len * sizeof(wchar_t));

    retVal = GetFullPathNameW(wPath, len, wAbsPath, NULL);
    mcx_free(wPath);
    if (0 == retVal) {
        mcx_free(wAbsPath);
        return NULL;
    } else {
        char * absPath = mcx_string_to_utf8(wAbsPath);
        mcx_free(wAbsPath);
        return absPath;
    }
}

int mcx_path_is_absolute(const char * path) {
    if (strlen(path) > 0) {
        if (path[0] == '/' || path[0] == '\\') {
            return 1;
        }
    }
    if (strlen(path) > 1) {
        if (path[1] == ':') {
            return 1;
        }
    }

    return 0;
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */