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
#include <stdexcept>

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

#include "default_response_callback.h"
#include "server_io.h"
#include "fault.h"

// #include "../response.h"
// #include "../request.h"
#include "../protocol_v1.h" // TODO
#include "../logger.h"
#include "../utils.h"
#include "../configuration.h"

#include "../../utf8_string.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace proxy {
  // Response*
  void
  DefaultResponseCallback::OnResponse (
    ::org::labcrypto::hottentot::runtime::Protocol *protocol,
    ::org::labcrypto::hottentot::runtime::Response *response
  ) {
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Response is received." << std::endl;
    }
    /* ResponseV1 *responseV1 = (ResponseV1 *)response;
    if (responseV1->GetStatusCode() == 0) {
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Response", responseV1->GetData(), responseV1->GetDataLength());
      }
      response_ = new ResponseV1();
      response_->Deserialize(responseV1->GetData(), responseV1->GetDataLength());
      responseReady_ = true;
    } else { */
    response_ = response;
    if (response_->GetStatusCode() != 0) {
      ResponseV1 *responseV1 = (ResponseV1 *)response;
      ::org::labcrypto::hottentot::Utf8String faultMessage;
      faultMessage.Deserialize(responseV1->GetData(), responseV1->GetDataLength());
      uint8_t responseStatusCode = response_->GetStatusCode();
      serverIO_->Close();
      // delete protocol;
      // delete tcpClient;
      throw 
        ::org::labcrypto::hottentot::runtime::proxy::Fault (
          responseStatusCode, 
          faultMessage.ToStdString()
        );
    }
    serverIO_->Close();
    responseProcessed_ = true;
    // delete protocol;
    // delete tcpClient;
  }
}
}
}
}
}