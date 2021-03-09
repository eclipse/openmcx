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

#include "util/libs.h"
#include "util/string.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


McxStatus mcx_dll_load(DllHandle * handle, const char * dllPath) {
    DllHandleCheck compValue;

    wchar_t * wDllPath = mcx_string_to_widechar(dllPath);

    * handle = LoadLibraryExW(wDllPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
    mcx_free(wDllPath);

    compValue = (DllHandleCheck) * handle;
    if (compValue <= HINSTANCE_ERROR) {
        LPVOID lpMsgBuf;
        DWORD err = GetLastError();

        mcx_log(LOG_ERROR, "Util: Dll (%s) could not be loaded", dllPath);

        switch (err) {
        case ERROR_BAD_EXE_FORMAT:
            mcx_log(LOG_ERROR, "Util: There is a mismatch in bitness (32/64) between current Model.CONNECT Execution Engine and the dynamic library", dllPath);
            break;
        default:
            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                err,
                0x0409, /* language id: us english */
                (LPTSTR) &lpMsgBuf,
                0,
                NULL);
            mcx_log(LOG_ERROR, "Util: Error %d: %s", err, lpMsgBuf);
            LocalFree(lpMsgBuf);
            break;
        }
        return RETURN_ERROR;
    }

    return RETURN_OK;
}


void * mcx_dll_get_function(DllHandle dllHandle, const char* functionName) {
    void * fp = NULL;

    fp = (void *) GetProcAddress(dllHandle, (char *) functionName);

    return fp;
}

void mcx_dll_free(DllHandle dllHandle)
{
    FreeLibrary(dllHandle);
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */