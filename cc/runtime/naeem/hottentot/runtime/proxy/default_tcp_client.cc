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

#include "default_tcp_client.h"

#include "../configuration.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        DefaultTcpClient::DefaultTcpClient(std::string host,
                                           uint32_t port)
            : TcpClient(host, port),
              socketFD_(0) {
        }
        DefaultTcpClient::~DefaultTcpClient() {
        }
        bool 
        DefaultTcpClient::Connect() {
#ifndef _MSC_VER
          struct sockaddr_in serverAddr;
          struct hostent *server;
          socketFD_ = socket(AF_INET, SOCK_STREAM, 0);
          if (socketFD_ < 0) {
            std::cerr << "ERROR opening socket" << std::endl;
            // exit(1);
            return false;
          }
          server = gethostbyname(host_.c_str());
          if (server == NULL) {
            std::cerr << "ERROR, no such host" << std::endl;
            // exit(1);
            return false;
          }
          memset((char *) &serverAddr, 0, sizeof(serverAddr));
          serverAddr.sin_family = AF_INET;
          // bcopy((char *)&serverAddr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
          serverAddr.sin_port = htons(port_);
          if (inet_pton(AF_INET, host_.c_str(), &serverAddr.sin_addr) <= 0) {
            std::cerr << "ERROR setting host" << std::endl;
            // exit(1);
            return false;
          }
          if (::naeem::hottentot::runtime::Configuration::SocketReadTimeout() > 0) {
            struct timeval tv;
            tv.tv_sec = ::naeem::hottentot::runtime::Configuration::SocketReadTimeout();
            tv.tv_usec = 0;
            if (setsockopt(socketFD_, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval)) < 0) {
              std::cerr << "ERROR setting read timeout." << std::endl;
              // exit(1);
              return false;
            }
          }
          if (connect(socketFD_, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "ERROR connecting" << std::endl;
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
              return false;
          }
          // Create a SOCKET for connecting to server
          socketFD_ = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
          if (socketFD_ == INVALID_SOCKET) {
              printf("socket failed with error: %ld\n", WSAGetLastError());
              WSACleanup();
              return false;
          }
          // Set recv timeout
          if (::naeem::hottentot::runtime::Configuration::SocketReadTimeout() > 0) {
            int nTimeout = ::naeem::hottentot::runtime::Configuration::SocketReadTimeout() * 1000;
            if (setsockopt(socketFD_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&nTimeout, sizeof(int)) != 0) {
              printf("setsockopt failed with error: %ld\n", WSAGetLastError());
              WSACleanup();
              return false;
            }
          }
          // Connect to server.
          iResult = connect(socketFD_, result->ai_addr, (int)result->ai_addrlen);
          if (iResult == SOCKET_ERROR) {
            closesocket(socketFD_);
            socketFD_ = INVALID_SOCKET;
            return false;
          }
          freeaddrinfo(result);
#endif
          return true;
        }
        void 
        DefaultTcpClient::Write(unsigned char *data,
                                uint32_t       dataLength) {
          if (dataLength == 0) {
            return;
          }
#ifndef _MSC_VER
          int result = write(socketFD_, data, dataLength * sizeof(unsigned char));
          if (result <= 0) {
            throw std::runtime_error("Write to service failed.");
          }
          /* for (uint32_t i = 0; i < dataLength; i++) {
            std::cout << "Writing ..." << std::endl;
            int result = write(socketFD_, &data[i], sizeof(unsigned char));
            std::cout << "Write result: " << result << std::endl;
            if (result <= 0) {
              throw std::runtime_error("Write to service failed.");
            }
            sleep(2);
          } */
#else
          int result = send(socketFD_, (char *)data, dataLength * sizeof(unsigned char), 0);
          if (result == SOCKET_ERROR) {
            throw std::runtime_error("Write to service failed.");
          }
#endif
        }
        uint32_t 
        DefaultTcpClient::Read(unsigned char *buffer,
                               uint32_t bufferLength) {
#ifndef _MSC_VER
          return read(socketFD_, buffer, bufferLength * sizeof(unsigned char));
#else
          return recv(socketFD_, (char *)buffer, bufferLength * sizeof(unsigned char), 0);
#endif
        }
        void 
        DefaultTcpClient::Close() {
          if (socketFD_ > 0) {
#ifndef _MSC_VER
            close(socketFD_);
#else
            closesocket(socketFD_);
#endif
            socketFD_ = 0;
          }
        }
      }
    }
  }
}
