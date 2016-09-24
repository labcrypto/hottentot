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
#include <limits>
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

#include "plain_server_connect_callback.h"
#include "server_connector.h"
#include "server_io.h"
#include "default_response_callback.h"
#include "proxy_runtime.h"
#include "server_write_callback_factory.h"

#include "../utils.h"
#include "../configuration.h"
#include "../logger.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace proxy {
  void 
  PlainServerConnectCallback::OnSuccess () {
    ::org::labcrypto::hottentot::runtime::proxy::ServerIO *serverIO = 
      serverConnector_->CreateServerIO();
    ::org::labcrypto::hottentot::runtime::ResponseCallback *responseCallback =
      new ::org::labcrypto::hottentot::runtime::proxy::DefaultResponseCallback(serverIO);
    ::org::labcrypto::hottentot::runtime::Protocol *protocol = 
      // new ::org::labcrypto::hottentot::runtime::ProtocolV1(/* tcpClient->GetRemoteSocketFD() */); // TODO(kamran): Use factory.
      ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::GetProtocolFactory()->Create();
    protocol->SetResponseCallback(responseCallback);
    uint32_t requestSerializedDataLength = 0;
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Serializing request object ..." << std::endl;
    }
    unsigned char *requestSerializedData = 
      protocol->SerializeRequest(request_, &requestSerializedDataLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request object is serialized." << std::endl;
    }
    /*
     * Send request byte array
     */
    uint32_t sendLength = 0;
    if (requestSerializedDataLength < 128) {
      sendLength = 1 + requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256) {
      sendLength = 2 + requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256 * 256) {
      sendLength = 3 + requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256 * 256 * 256) {
      sendLength = 4 + requestSerializedDataLength;
    } else if (requestSerializedDataLength <= std::numeric_limits<uint32_t>::max()) {
      sendLength = 5 + requestSerializedDataLength;
    }
    unsigned char *sendData = new unsigned char[sendLength];
    uint32_t c = 0;
    if (requestSerializedDataLength < 128) {
      sendData[c++] = requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256) {
      sendData[c++] = 0x81;
      sendData[c++] = requestSerializedDataLength;
    } else if (requestSerializedDataLength < 256 * 256) {
      sendData[c++] = 0x82;
      sendData[c++] = requestSerializedDataLength / 256;
      sendData[c++] = requestSerializedDataLength % 256;
    } else if (requestSerializedDataLength < 256 * 256 * 256) {
      sendData[c] = 0x83;
      sendData[c + 1] = requestSerializedDataLength / (256 * 256);
      sendData[c + 2] = (requestSerializedDataLength - sendData[c + 1] * 256 * 256) / 256;
      sendData[c + 3] = requestSerializedDataLength % (256 * 256);
      c += 4;
    } else if (requestSerializedDataLength <= std::numeric_limits<uint32_t>::max()) {
      sendData[c] = 0x84;
      sendData[c + 1] = requestSerializedDataLength / (256 * 256 * 256);
      sendData[c + 2] = (requestSerializedDataLength - sendData[c + 1] * 256 * 256 * 256) / (256 * 256);
      sendData[c + 3] = (requestSerializedDataLength - sendData[c + 1] * 256 * 256 * 256 - sendData[c + 2] * 256 * 256) / 256;
      sendData[c + 4] = requestSerializedDataLength % (256 * 256 * 256);
      c += 5;
    }
    for (uint32_t i = 0; i < requestSerializedDataLength; i++) {
      sendData[c++] = requestSerializedData[i];
    }
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Writing " << sendLength << " Bytes to socket ..." << std::endl;
      ::org::labcrypto::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
    }
    // ServerWriteCallbackFactory *serverWriteCallbackFactory = new PlainBlockingServerWriteCallbackFactory(); // TODO: Use abstract factory
    ServerWriteCallback *serverWriteCallback = 
      // serverWriteCallbackFactory.Create(serverIO, protocol);
      ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::GetServerWriteCallbackFactory()->Create(serverIO, protocol);
    serverIO->SetServerWriteCallback(serverWriteCallback);
    // try {
    serverIO->Write(sendData, sendLength);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
      "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
        "Write request is sent." << std::endl;
    }
    /*} catch (std::exception &e) {
      delete protocol;
      delete serverConnector;
      delete serverIO;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: " + e.what());
    } catch (...) {
      delete protocol;
      delete serverConnector;
      delete serverIO;
      delete [] sendData;
      delete [] requestSerializedData;
      throw std::runtime_error("[" + ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() + "]: Exception occurred while writing to server socket.");
    } */
    /* delete [] sendData;
    delete [] requestSerializedData; */
  }
   void 
  PlainServerConnectCallback::OnFailure () {
  }
}
}
}
}
}