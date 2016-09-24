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

#include "plain_server_write_callback.h"
#include "server_io.h"


#include "../utils.h"
#include "../protocol_v1.h"
#include "../configuration.h"
#include "../logger.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace proxy {
  void 
  PlainServerWriteCallback::OnSuccess () {
    ServerReadCallback *serverReadCallback = 
      // serverWriteCallbackFactory.Create(serverIO, protocol);
      ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::GetServerReadCallbackFactory()->Create(serverIO, protocol);
    serverIO->SetServerReadCallback(serverReadCallback);
    serverIO->StartReading();
    /* if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Waiting for response ..." << std::endl;
    }
    unsigned char buffer[256];
    while (!protocol_->GetResponseCallback()->IsResponseProcessed()) { // CCC
      int numOfReadBytes = serverIO_->Read(buffer, 256);
      if (numOfReadBytes == 0) {
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
      }
      protocol_->FeedResponseData(buffer, numOfReadBytes);
    } */
    /*
     * Response deserialization
     */
    /* ::org::labcrypto::hottentot::runtime::ResponseV1 *responseV1 = 
      (::org::labcrypto::hottentot::runtime::ResponseV1 *)protocol_->GetResponseCallback()->GetResponse();
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Utils::PrintArray (
        "Response", 
        responseV1->GetData(), 
        responseV1->GetDataLength()
      );
    }
    out.Deserialize (
      responseV1->GetData(), 
      responseV1->GetDataLength()
    ); */
  }
  void 
  PlainServerWriteCallback::OnFailure () {
  }
}
}
}
}
}