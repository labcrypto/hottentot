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
#include <limits>


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

#include "default_request_callback.h"
#include "request_handler.h"
#include "client_io.h"

// #include "../response.h"
// #include "../request.h"
#include "../protocol_v1.h" // TODO
#include "../logger.h"
#include "../utils.h"
#include "../configuration.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace service {
  // Response*
  void
  DefaultRequestCallback::OnRequest (
    ::org::labcrypto::hottentot::runtime::Protocol *protocol,
    ::org::labcrypto::hottentot::runtime::Request *request
  ) {
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "A new request is received." << std::endl;
    }
    if (requestHandlers_->count(request->GetServiceId()) > 0) {
      Response *response = new ResponseV1; // TODO Use factory
      RequestHandler *requestHandler = requestHandlers_->find(request->GetServiceId())->second;
      if (requestHandler == 0) {
        throw std::runtime_error("Request handler is null.");
      }
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
          "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
            "Calling handler method ..." << std::endl;
      }
      requestHandler->HandleRequest(*request, *response);
      // return response;
      uint32_t responseSerializedLength = 0;
      unsigned char *responseSerializedData = protocol->SerializeResponse(response, &responseSerializedLength);
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
          "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
            "Writing response back to client ..." << std::endl;
      }
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Serialized response", responseSerializedData, responseSerializedLength);
      }
      uint32_t sendLength = 0;
      if (responseSerializedLength < 128) {
        sendLength = 1 + responseSerializedLength;
      } else if (responseSerializedLength < 256) {
        sendLength = 2 + responseSerializedLength;
      } else if (responseSerializedLength < 256 * 256) {
        sendLength = 3 + responseSerializedLength;
      } else if (responseSerializedLength < 256 * 256 * 256) {
        sendLength = 4 + responseSerializedLength;
      } else if (responseSerializedLength <= std::numeric_limits<uint32_t>::max()) {
        sendLength = 5 + responseSerializedLength;
      }
      unsigned char *sendData = new unsigned char[sendLength];
      uint32_t c = 0;
      if (responseSerializedLength < 128) {
        sendData[c++] = responseSerializedLength;
      } else if (responseSerializedLength < 256) {
        sendData[c++] = 0x81;
        sendData[c++] = responseSerializedLength;
      } else if (responseSerializedLength < 256 * 256) {
        sendData[c++] = 0x82;
        sendData[c++] = responseSerializedLength / 256;
        sendData[c++] = responseSerializedLength % 256;
      } else if (responseSerializedLength < 256 * 256 * 256) {
        sendData[c] = 0x83;
        sendData[c + 1] = responseSerializedLength / (256 * 256);
        sendData[c + 2] = (responseSerializedLength - sendData[c + 1] * 256 * 256) / 256;
        sendData[c + 3] = responseSerializedLength % (256 * 256);
        c += 4;
      } else if (responseSerializedLength <= std::numeric_limits<uint32_t>::max()) {
        sendData[c] = 0x84;
        sendData[c + 1] = responseSerializedLength / (256 * 256 * 256);
        sendData[c + 2] = (responseSerializedLength - sendData[c + 1] * 256 * 256 * 256) / (256 * 256);
        sendData[c + 3] = (responseSerializedLength - sendData[c + 1] * 256 * 256 * 256 - sendData[c + 2] * 256 * 256) / 256;
        sendData[c + 4] = responseSerializedLength % (256 * 256 * 256);
        c += 5;
      }
      for (unsigned int k = 0; k < responseSerializedLength; k++) {
        sendData[c++] = responseSerializedData[k];
      }
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
      } 
      try {
        clientIO_->Write(sendData, sendLength);
      } catch (std::exception &e) {
        ::org::labcrypto::hottentot::runtime::Logger::GetError() <<
          "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
             e.what() << std::endl;
      }
      clientIO_->Close();
    } else {
      throw std::runtime_error("Service id is not found.");           
    }
  }
}
}
}
}
}