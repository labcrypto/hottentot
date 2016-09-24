/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifdef _MSC_VER
// #include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdexcept>
#include <iostream>
#include <sstream>

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#include <unistd.h>
#endif

#include "plain_blocking_tcp_server_connector.h"
#include "plain_blocking_socket_server_io.h"
#include "server_connect_callback.h"

#include "../utils.h"
#include "../configuration.h"
#include "../logger.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace proxy {
  ServerIO* 
  PlainBlockingTcpServerConnector::CreateServerIO() {
    return new PlainBlockingSocketServerIO(socketFD_);
  }
  bool
  PlainBlockingTcpServerConnector::Connect() {
#ifndef _MSC_VER
    struct sockaddr_in serverAddr;
    struct hostent *server;
    socketFD_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD_ < 0) {
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        std::cerr << 
          "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
            "ERROR opening socket" << std::endl;
      }
      if (serverConnectCallback_) {
        serverConnectCallback_->OnFailure();
      }
      // exit(1);
      return false;
    }
    server = gethostbyname(host_.c_str());
    if (server == NULL) {
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        std::cerr << 
          "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
            "ERROR, no such host" << std::endl;
      }
      close(socketFD_);
      if (serverConnectCallback_) {
        serverConnectCallback_->OnFailure();
      }
      // exit(1);
      return false;
    }
    memset((char *) &serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    // bcopy((char *)&serverAddr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serverAddr.sin_port = htons(port_);
    if (inet_pton(AF_INET, host_.c_str(), &serverAddr.sin_addr) <= 0) {
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        std::cerr << 
          "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
            "ERROR setting host" << std::endl;
      }
      close(socketFD_);
      if (serverConnectCallback_) {
        serverConnectCallback_->OnFailure();
      }
      // exit(1);
      return false;
    }
    if (::org::labcrypto::hottentot::runtime::Configuration::SocketReadTimeout() > 0) {
      struct timeval tv;
      tv.tv_sec = ::org::labcrypto::hottentot::runtime::Configuration::SocketReadTimeout();
      tv.tv_usec = 0;
      if (setsockopt(socketFD_, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval)) < 0) {
        if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
          std::cerr << 
            "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
              "ERROR setting read timeout." << std::endl;
        }
        close(socketFD_);
        if (serverConnectCallback_) {
          serverConnectCallback_->OnFailure();
        }
        // exit(1);
        return false;
      }
    }
    if (connect(socketFD_, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        std::cerr << 
          "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
            "ERROR connecting" << std::endl;
      }
      close(socketFD_);
      if (serverConnectCallback_) {
        serverConnectCallback_->OnFailure();
      }
      // exit(1);
      return false;
    }
#else
    WSADATA wsaData;
    struct addrinfo *result = NULL,
                    hints;
    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        if (serverConnectCallback_) {
          serverConnectCallback_->OnFailure();
        }
        return false;
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    std::stringstream ss;
    ss << port_;
    iResult = getaddrinfo(host_.c_str(), ss.str().c_str(), &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        if (serverConnectCallback_) {
          serverConnectCallback_->OnFailure();
        }
        return false;
    }
    // Create a SOCKET for connecting to server
    socketFD_ = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (socketFD_ == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        if (serverConnectCallback_) {
          serverConnectCallback_->OnFailure();
        }
        return false;
    }
    // Set recv timeout
    if (::org::labcrypto::hottentot::runtime::Configuration::SocketReadTimeout() > 0) {
      int nTimeout = ::org::labcrypto::hottentot::runtime::Configuration::SocketReadTimeout() * 1000;
      if (setsockopt(socketFD_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&nTimeout, sizeof(int)) != 0) {
        printf("setsockopt failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        if (serverConnectCallback_) {
          serverConnectCallback_->OnFailure();
        } 
        return false;
      }
    }
    // Connect to server.
    iResult = connect(socketFD_, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
      closesocket(socketFD_);
      socketFD_ = INVALID_SOCKET;
      if (serverConnectCallback_) {
        serverConnectCallback_->OnFailure();
      }
      return false;
    }
    freeaddrinfo(result);
#endif
    if (serverConnectCallback_) {
      serverConnectCallback_->OnSuccess();
    }
    return true;
  }
}
}
}
}
}