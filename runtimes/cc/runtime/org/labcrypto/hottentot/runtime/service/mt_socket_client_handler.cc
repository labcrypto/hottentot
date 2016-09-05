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

#include "mt_socket_client_handler.h"
#include "plain_blocking_socket_client_io.h"
#include "default_request_callback.h"
#include "default_response_callback.h"

#include "../logger.h"
#include "../utils.h"
#include "../configuration.h"
#include "../protocol_v1.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace service {
  void
  MTSocketClientHandler::Handle() {
    _HandleClientThreadParams *params = new _HandleClientThreadParams;
    params->clientHandler_ = this;
    params->clientSocketFD_ = clientSocketFD_;
#ifndef _MSC_VER
    pthread_t thread; // TODO(kamran): We need a thread pool here.
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int ret = pthread_create(&thread, &attr, HandleClientConnection, (void *)params);
    if (ret) {
      ::org::labcrypto::hottentot::runtime::Logger::GetError() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Error - pthread_create() return code: " << ret << std::endl;
      exit(EXIT_FAILURE);
    }
    // pthread_detach(ret);
#else
    HANDLE res = CreateThread (
      NULL,
      0,
      HandleClientConnection,
      (LPVOID)params,
      0,
      NULL
    );
    if (res == NULL) {
      printf("Handler thread couldn't start: %d\n", WSAGetLastError());
      closesocket(ref->serverSocketFD_);
      WSACleanup();
      exit(EXIT_FAILURE);
    }
#endif
  }
#ifndef _MSC_VER
  void*
  MTSocketClientHandler::HandleClientConnection(void *data) {
#else
  DWORD WINAPI
  MTSocketClientHandler::HandleClientConnection(LPVOID data) {
#endif
    bool ok = true;
    _HandleClientThreadParams *ref = (_HandleClientThreadParams*)data;
    unsigned char buffer[256];
    ::org::labcrypto::hottentot::runtime::Protocol *protocol = 
      new ::org::labcrypto::hottentot::runtime::ProtocolV1(); // TODO: User factory
    // TODO: Create ClientIO
    ClientIO *clientIO = new PlainBlockingSocketClientIO(ref->clientSocketFD_); // TODO: Use factory
    RequestCallback *requestCallback = 
      new DefaultRequestCallback (
        clientIO, 
        ref->clientHandler_->requestHandlers_
      ); // TODO: User factory
    protocol->SetRequestCallback(requestCallback);
    // TODO: Create ResponseCallback
    ResponseCallback *responseCallback = 
      new DefaultResponseCallback(clientIO); // TODO: User factory
    protocol->SetResponseCallback(responseCallback);
    while (ok) {
      int numOfReadBytes = clientIO->Read(buffer, 256);
      if (numOfReadBytes <= 0) {
        ok = false;
      }
      if (ok) {
        if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
          ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Read", buffer, numOfReadBytes);
        }
        protocol->FeedRequestData(buffer, numOfReadBytes);
      }
    }
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Client is gone." << std::endl;
    }
    clientIO->Close();
    delete requestCallback;
    delete protocol;
    delete ref;
#ifndef _MSC_VER
    pthread_exit(NULL);
#endif
    return 0;
  }
}
}
}
}
}