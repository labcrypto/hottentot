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
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>

#include "default_tcp_client.h"


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
        void 
        DefaultTcpClient::Connect() {
          struct sockaddr_in serverAddr;
          struct hostent *server;
          socketFD_ = socket(AF_INET, SOCK_STREAM, 0);
          if (socketFD_ < 0) {
            std::cerr << "ERROR opening socket" << std::endl;
            exit(1);
          }
          server = gethostbyname(host_.c_str());
          if (server == NULL) {
            std::cerr << "ERROR, no such host" << std::endl;
            exit(1);
          }
          memset((char *) &serverAddr, 0, sizeof(serverAddr));
          serverAddr.sin_family = AF_INET;
          // bcopy((char *)&serverAddr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
          serverAddr.sin_port = htons(port_);
          if (inet_pton(AF_INET, host_.c_str(), &serverAddress.sin_address)) {
            std::cerr << "ERROR setting host" << std::endl;
            exit(1);
          }
          if (connect(socketFD_, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "ERROR connecting" << std::endl;
            exit(1);
          }
        }
        void 
        DefaultTcpClient::Write(unsigned char *data,
                                uint32_t       dataLength) {
          write(socketFD_, data, dataLength * sizeof(unsigned char));
        }
        uint32_t 
        DefaultTcpClient::Read(unsigned char *buffer,
                               uint32_t bufferLength) {
          return read(socketFD_, buffer, bufferLength * sizeof(unsigned char));
        }
        void 
        DefaultTcpClient::Close() {
          if (socketFD_ > 0) {
            close(socketFD_);
            socketFD_ = 0;
          }
        }
      }
    }
  }
}
