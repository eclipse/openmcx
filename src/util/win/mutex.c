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

#if defined (ENABLE_MT)
#include "util/mutex.h"

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


void mcx_mutex_create( McxMutex* mutex )
{
    InitializeCriticalSection( mutex );
}

void mcx_mutex_destroy( McxMutex* mutex )
{
    DeleteCriticalSection( mutex );
}

void mcx_mutex_lock( McxMutex * mutex )
{
    EnterCriticalSection( mutex );
}


int mcx_mutex_try_lock( McxMutex * mutex )
{
    return TryEnterCriticalSection( mutex );
}


void mcx_mutex_unlock( McxMutex * mutex )
{
    LeaveCriticalSection( mutex );
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // ENABLE_MT