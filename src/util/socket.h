/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_UTIL_SOCKET_H
#define MCX_UTIL_SOCKET_H

#if defined(OS_WINDOWS)

  #include <winsock2.h>
  #include <ws2tcpip.h>

  typedef SOCKET McxSocket;

  typedef int socklen_t;
  #define mcx_socket_close(s) closesocket(s)
#elif defined(OS_LINUX)
  #include <unistd.h>

  #include <netinet/in.h>
  #include <netinet/tcp.h>

  #define SOCKET_ERROR (-1)

  #define mcx_socket_close(s) close(s)

  typedef int McxSocket;

#endif

#if defined (ENABLE_MT)
  int mcx_socket_set_timeout(McxSocket sockfd, int msTimeout);
  int mcx_socket_set_nodelay(McxSocket sockfd, int noDelay);
#endif // defined (ENABLE_MT)

#endif // MCX_UTIL_SOCKET_H