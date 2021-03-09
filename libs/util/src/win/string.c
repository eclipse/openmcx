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

#include "common/logging.h"
#include "common/memory.h"

#include "util/string.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

wchar_t * mcx_string_to_widechar(const char * str) {
    int wchars_num =  MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wchar_t * wstr = NULL;

    if (0 == wchars_num) {
        return NULL;
    }
    wstr = (wchar_t *) mcx_calloc(wchars_num, sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, wchars_num);

    return wstr;
}

char * mcx_string_to_utf8(const wchar_t * wstr) {
    int str_num = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char * str = NULL;

    if (0 == str_num) {
        return NULL;
    }

    str = (char *) mcx_calloc(str_num, sizeof(char));
    if (!str) {
        return NULL;
    }

    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, str_num, NULL, NULL);

    return str;
}

char * mcx_string_mbcs_to_utf8(const char * str) {
    size_t wcs_size, num_converted;
    errno_t ret_val;
    char *utf8_str;
    wchar_t *buffer;

    // find out the required size of the wide character string
    ret_val = mbstowcs_s(&wcs_size, NULL, 0, str, 0);
    if (ret_val) {
        mcx_log(LOG_ERROR, "Could not decode given string %s based on the current locale.", str);
        return NULL;
    }

    // allocate memory required for the buffer
    buffer = (wchar_t *)mcx_calloc(wcs_size, sizeof(wchar_t));
    if (!buffer) {
        return NULL;
    }

    // convert the local encoded string into a wide character string
    ret_val = mbstowcs_s(&num_converted, buffer, wcs_size, str, _TRUNCATE);
    if (ret_val) {
        mcx_log(LOG_ERROR, "Could not decode given string %s based on the current locale.", str);
        return NULL;
    }

    // convert the wide character string into a UTF-8 encoded string
    utf8_str = mcx_string_to_utf8(buffer);
    mcx_free(buffer);
    return utf8_str;
}

int mcx_string_cmpi(const char * left, const char * right) {
    return _stricmp(left, right);
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */