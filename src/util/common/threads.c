/********************************************************************************
 * Copyright (c) 2021 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#if defined (ENABLE_MT)

#include "util/threads.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int mcx_run_with_timeout(McxThreadStartRoutine fn, McxThreadParameter arg, long * retVal, int timeoutSec) {
    McxThread thread;

    if (mcx_thread_create(&thread, fn, arg)) {
        return 1;
    }

    if (mcx_thread_join_with_timeout(thread, retVal, timeoutSec)) {
        mcx_thread_terminate(thread);
        return 1;
    }

    return 0;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // ENABLE_MT