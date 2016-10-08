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

#include "plain_blocking_socket_service_io.h"
#include "service_write_callback.h"
#include "service_read_callback.h"
#include "service_close_callback.h"

#include "../utils.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace proxy {
  void 
  PlainBlockingSocketServiceIO::Read() {
/* #ifndef _MSC_VER
    return read(socketFD_, buffer, length * sizeof(unsigned char));
#else
    return recv(socketFD_, (char *)buffer, length * sizeof(unsigned char), 0);
#endif */
    stopped_ = false;
    unsigned char data[256];
    while (!stopped_) {
#ifndef _MSC_VER
      int numOfReadBytes = read(socketFD_, data, 256 * sizeof(unsigned char));
#else
      int numOfReadBytes = recv(socketFD_, (char *)data, 256 * sizeof(unsigned char), 0);
#endif
      uint32_t bufferLength = 0;
      unsigned char *buffer = NULL;
      /* if (numOfReadBytes == 0) {
        // delete protocol;
        // delete serverConnector;
        // delete serverIO;
        throw std::runtime_error("[" + 
          ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + 
          "]: Service is gone.");
      }
      if (numOfReadBytes < 0) {
        // delete protocol;
        // delete serverConnector;
        // delete serverIO;
        throw std::runtime_error("[" + 
          ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + 
          "]: Read from service failed.");
      } */
      if (numOfReadBytes > 0) {
        bufferLength = numOfReadBytes;
        buffer = (unsigned char *) malloc(bufferLength * sizeof(unsigned char));
        memcpy(buffer, data, bufferLength);
      }
      // protocol_->FeedResponseData(buffer, numOfReadBytes);
      if (serviceReadCallback_) {
        serviceReadCallback_->OnData(buffer, numOfReadBytes, bufferLength);
      }
    } 
  }
  void
  PlainBlockingSocketServiceIO::Stop() {
    stopped_ = true;
  }
  void 
  PlainBlockingSocketServiceIO::Write (
    unsigned char *buffer,
    uint32_t length
  ) {
#ifndef _MSC_VER
    int result = write(socketFD_, buffer, length * sizeof(unsigned char));
    if (result <= 0) {
      if (serviceWriteCallback_) {
        serviceWriteCallback_->OnFailure();
        return;
      }
      // throw std::runtime_error("[" + Utils::GetCurrentUTCTimeString() + "]: Write failed.");
    }
#else
    int result = send(socketFD_, (char *)buffer, length * sizeof(unsigned char), 0);
    if (result == SOCKET_ERROR) {
      if (serviceWriteCallback_) {
        serviceWriteCallback_->OnFailure();
        return;
      }
      // throw std::runtime_error("[" + Utils::GetCurrentUTCTimeString() + "]: Write failed.");
    }
#endif
    if (serviceWriteCallback_) {
      serviceWriteCallback_->OnSuccess();
    }
  }
  void 
  PlainBlockingSocketServiceIO::Close() {
    if (socketFD_ > 0) {
#ifndef _MSC_VER
      close(socketFD_);
#else
      closesocket(socketFD_);
#endif
      socketFD_ = 0;
      if (serviceCloseCallback_) {
        serviceCloseCallback_->OnSuccess();
      }
    }
  }
}
}
}
}
}