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

#include "util/threads.h"
#include "util/os.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int mcx_thread_create(McxThread * handle, McxThreadStartRoutine start_routine, McxThreadParameter arg)
{
    * handle = CreateThread(NULL, 0, start_routine, arg, 0, NULL);
    if (!*handle) {
        mcx_log(LOG_ERROR, "Error creating thread");
        return 1;
    }

    return 0;
}

int mcx_thread_terminate(McxThread handle) {
    return TerminateThread(handle, 0);
}

void mcx_thread_exit(long ret) {
    ExitThread(ret);
}

int mcx_thread_join(McxThread handle, long * ret) {
    long exitCode;
    WaitForSingleObject(handle, INFINITE );
    GetExitCodeThread(handle, (LPDWORD) &exitCode);
    *ret = exitCode;
    CloseHandle(handle);
    return 0;
}

int mcx_thread_join_with_timeout(McxThread handle, long * ret, int secs) {
    long exitCode;

    DWORD status = WaitForSingleObject(handle, secs * 1000);

    switch (status) {
    case WAIT_ABANDONED:
        mcx_log(LOG_ERROR, "thread_join_with_timeout: Wait abandoned");
        return 1;
    case WAIT_TIMEOUT:
        mcx_log(LOG_ERROR, "thread_join_with_timeout: Timed out");
        return 1;
    case WAIT_FAILED:
        mcx_log(LOG_ERROR, "thread_join_with_timeout: Wait failed");
        goto error;
    case WAIT_OBJECT_0:
        // ok
        break;
    }

    if (!GetExitCodeThread(handle, (LPDWORD) &exitCode)) {
        goto error;
    }

    *ret = exitCode;
    if (!CloseHandle(handle)) {
        goto error;
    }

    return 0;

error:
    char * error = mcx_os_win_get_last_error();
    mcx_log(LOG_ERROR, "thread_join_with_timeout: %s", error);
    mcx_free(error);
    return 1;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // ENABLE_MT