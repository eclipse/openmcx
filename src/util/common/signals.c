/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "util/signals.h"

#include "CentralParts.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


// For ctrl-c handling
static int _taskInterrupted = 0;

int mcx_signal_handler_is_interrupted() {
    return _taskInterrupted;
}

void mcx_signal_handler_sigint(int param) {
    if (!_taskInterrupted) {
        mcx_log(LOG_INFO, "Caught Ctrl-C. Stopping.");

        _taskInterrupted = 1;
    } else {
        mcx_log(LOG_INFO, "Caught Ctrl-C again. Exiting.");

        exit(1);
    }
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */