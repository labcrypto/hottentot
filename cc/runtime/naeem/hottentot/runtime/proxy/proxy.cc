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
// #include <winsock2.h>
// #include <ws2tcpip.h>
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
#include <iostream>

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

#include "proxy.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        void
        Proxy::Destroy() {
          // TODO(kamran)
        }
        bool
        Proxy::IsServerAlive() {
          struct sockaddr_in serverAddr;
          struct hostent *server;
          int socketFD = socket(AF_INET, SOCK_STREAM, 0);
          if (socketFD < 0) {
            std::cerr << "ERROR opening socket" << std::endl;
            return false;
          }
          server = gethostbyname(host_.c_str());
          if (server == NULL) {
            std::cerr << "ERROR, no such host" << std::endl;
            return false;
          }
          memset((char *) &serverAddr, 0, sizeof(serverAddr));
          serverAddr.sin_family = AF_INET;
          serverAddr.sin_port = htons(port_);
          if (inet_pton(AF_INET, host_.c_str(), &serverAddr.sin_addr) <= 0) {
            std::cerr << "ERROR setting host" << std::endl;
            return false;
          }
          if (connect(socketFD, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "ERROR connecting to host" << std::endl;
            return false;
          }
          close(socketFD);
          return true;
        }
      }
    }
  }
}