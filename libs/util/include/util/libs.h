/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_UTIL_LIBS_H
#define MCX_UTIL_LIBS_H

#include "common/status.h"


#if defined(OS_WINDOWS)
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>
  typedef HINSTANCE DllHandle;
  #ifdef OS_64
    typedef __int64 DllHandleCheck;
  #else
    typedef int     DllHandleCheck;
  #endif
#elif defined(OS_LINUX)
  typedef void *    DllHandleCheck;
  typedef void *    DllHandle;
#else
  #error Unsupported Platform
#endif


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


McxStatus mcx_dll_load(DllHandle * handle, const char * dllPath);

void * mcx_dll_get_function(DllHandle dllHandle, const char * functionName);

void mcx_dll_free(DllHandle dllHandle);

#if defined (OS_LINUX)
McxStatus mcx_dll_load_global(DllHandle * handle, const char * dllPath);
#endif // OS_LINUX

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // MCX_UTIL_LIBS_H