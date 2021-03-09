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

#include "util/socket.h"

#include <winsock2.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int mcx_socket_set_timeout(McxSocket sockfd, int msTimeout) {
    return setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&msTimeout, sizeof msTimeout);
}

int mcx_socket_set_nodelay(McxSocket sockfd, int noDelay) {
    const char _noDelay = noDelay;
    return setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &_noDelay, sizeof(_noDelay));
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif //ENABLE_MT