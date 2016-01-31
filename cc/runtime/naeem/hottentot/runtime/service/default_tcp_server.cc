/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>

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
#endif

#include "../logger.h"
#include "../utils.h"
#include "../protocol_v1.h"
#include "../configuration.h"

#include "default_tcp_server.h"
#include "default_request_callback.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        DefaultTcpServer::DefaultTcpServer(std::string host,
                                           uint16_t port,
                                           std::map<uint8_t, RequestHandler*> *requestHandlers)
            : TcpServer(host, port, requestHandlers), 
              serverSocketFD_(-1) {
        }
        DefaultTcpServer::~DefaultTcpServer() {
        }
        void
        DefaultTcpServer::BindAndStart() {
          if (serverSocketFD_ < 0) {
#ifndef _MSC_VER
            struct sockaddr_in servAddr;
            int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
            memset((char *) &servAddr, 0, sizeof(servAddr));
            servAddr.sin_family = AF_INET;
            servAddr.sin_addr.s_addr = INADDR_ANY;
            servAddr.sin_port = htons(port_);
            if (bind(serverSocketFD, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
              ::naeem::hottentot::runtime::Logger::GetError() << "Error on bind." << std::endl;
              exit(EXIT_FAILURE);
            }
            listen(serverSocketFD, 5);
            serverSocketFD_ = serverSocketFD;
            pthread_t thread;
            int ret = pthread_create(&thread, NULL, AcceptClients, (void *)this);
            if (ret) {
              ::naeem::hottentot::runtime::Logger::GetError() << "Error - pthread_create() return code: " << ret << std::endl;
              exit(EXIT_FAILURE);
            }
#else
            WSADATA wsaData;
            struct addrinfo *result = NULL;
            struct addrinfo hints;
            // Initialize Winsock
            int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
            if (iResult != 0) {
              printf("WSAStartup failed with error: %d\n", iResult);
              exit(1);
            }
            ZeroMemory(&hints, sizeof(hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;
            hints.ai_flags = AI_PASSIVE;
            // Resolve the server address and port
            std::stringstream ss;
            ss << port_;
            iResult = getaddrinfo(NULL, ss.str().c_str(), &hints, &result);
            if (iResult != 0) {
              printf("getaddrinfo failed with error: %d\n", iResult);
              WSACleanup();
              return;
            }
            // Create a SOCKET for connecting to server
            serverSocketFD_ = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
            if (serverSocketFD_ == INVALID_SOCKET) {
              printf("socket failed with error: %ld\n", WSAGetLastError());
              freeaddrinfo(result);
              WSACleanup();
              return;
            }
            // Setup the TCP listening socket
            iResult = bind(serverSocketFD_, result->ai_addr, (int)result->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
              printf("bind failed with error: %d\n", WSAGetLastError());
              freeaddrinfo(result);
              closesocket(serverSocketFD_);
              WSACleanup();
                return;
            }
            freeaddrinfo(result);
            iResult = listen(serverSocketFD_, SOMAXCONN);
            if (iResult == SOCKET_ERROR) {
              printf("listen failed with error: %d\n", WSAGetLastError());
              closesocket(serverSocketFD_);
              WSACleanup();
              return;
            }

#endif
          }
        }
#ifndef _MSC_VER
        void*
        DefaultTcpServer::AcceptClients(void *data) {
#else
        DWORD WINAPI
        DefaultTcpServer::AcceptClients(LPVOID data) {
#endif
          bool ok = true;
#ifndef _MSC_VER
          struct sockaddr_in clientAddr;
          socklen_t clientAddrLength = sizeof(clientAddr);
#endif
          SOCKET clientSocket = INVALID_SOCKET;
          DefaultTcpServer *ref = (DefaultTcpServer*)data;
          while (ok) {
#ifndef _MSC_VER
            int clientSocketFD = accept(ref->serverSocketFD_, (struct sockaddr *) &clientAddr, &clientAddrLength);
#else
            clientSocket = accept(ref->serverSocketFD_, NULL, NULL);
            if (clientSocket == INVALID_SOCKET) {
                printf("accept failed with error: %d\n", WSAGetLastError());
                closesocket(ref->serverSocketFD_);
                WSACleanup();
                return 1;
            }
#endif
            if (::naeem::hottentot::runtime::Configuration::Verbose()) {
              ::naeem::hottentot::runtime::Logger::GetOut() << "A new client is connected." << std::endl;
            }
            _HandleClientConnectionParams *params = new _HandleClientConnectionParams;
            params->tcpServer_ = ref;
#ifndef _MSC_VER
            params->clientSocketFD_ = clientSocketFD;
#endif
#ifndef _MSC_VER
            pthread_t thread; // TODO(kamran): We need a thread pool here.
            int ret = pthread_create(&thread, NULL, HandleClientConnection, (void *)params);
            if (ret) {
              ::naeem::hottentot::runtime::Logger::GetError() << "Error - pthread_create() return code: " << ret << std::endl;
              exit(EXIT_FAILURE);
            }
#endif
          }
          return 0;
        }
#ifndef _MSC_VER
        void*
        DefaultTcpServer::HandleClientConnection(void *data) {
#else
        DWORD WINAPI
        DefaultTcpServer::HandleClientConnection(LPVOID data) {
#endif
          bool ok = true;
          _HandleClientConnectionParams *ref = (_HandleClientConnectionParams*)data;
          unsigned char buffer[256];
          ::naeem::hottentot::runtime::Protocol *protocol = 
            new ::naeem::hottentot::runtime::ProtocolV1(ref->clientSocketFD_);
          DefaultRequestCallback *requestCallback = new DefaultRequestCallback(ref->tcpServer_->requestHandlers_);
          protocol->SetRequestCallback(requestCallback);
          while (ok) {
#ifndef _MSC_VER
            uint32_t numOfReadBytes = read(ref->clientSocketFD_, buffer, 256);
#else
            uint32_t numOfReadBytes = 0; // TODO
#endif
            if (numOfReadBytes <= 0) {
              ok = false;
            }
            if (ok) {
              if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                ::naeem::hottentot::runtime::Utils::PrintArray("Read", buffer, numOfReadBytes);
              }
              protocol->ProcessDataForRequest(buffer, numOfReadBytes);
            }
          }
          if (::naeem::hottentot::runtime::Configuration::Verbose()) {
            ::naeem::hottentot::runtime::Logger::GetOut() << "Client is gone." << std::endl;
          }
#ifndef _MSC_VER
          close(ref->clientSocketFD_);
#endif
          delete requestCallback;
          delete protocol;
          delete ref;
          return 0;
        }
      }
    }
  }
}