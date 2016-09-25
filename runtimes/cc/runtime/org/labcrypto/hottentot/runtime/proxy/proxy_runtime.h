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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_PROXY__PROXY_RUNTIME_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_PROXY__PROXY_RUNTIME_H_

#include <vector>
#include <map>
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


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
  class ProtocolFactory;
  class Response;
namespace proxy {
  class ServiceConnectorFactory;
  class ServiceConnectCallbackFactory;
  class ServiceWriteCallbackFactory;
  class ServiceReadCallbackFactory;
  class ProxyRuntime {
  public:
    static void Init (
      int argc, 
      char **argv
    );
    static void Shutdown();
  public:
    static ::org::labcrypto::hottentot::runtime::ProtocolFactory* GetProtocolFactory();
    static ServiceConnectorFactory* GetServiceConnectorFactory();
    static ServiceConnectCallbackFactory* GetServiceConnectCallbackFactory();
    static ServiceWriteCallbackFactory* GetServiceWriteCallbackFactory();
    static ServiceReadCallbackFactory* GetServiceReadCallbackFactory();
    static Response* GetResponse(uint64_t requestId) {
      return responses_[requestId];
    }
    static void StoreResponse(uint64_t requestId, ::org::labcrypto::hottentot::runtime::Response *response) {
      // TODO If already we have the request id in the map.
      responses_[requestId] = response;
    }
  private:
    static ::org::labcrypto::hottentot::runtime::ProtocolFactory *protocolFactory_;
    static ServiceConnectorFactory *serviceConnectorFactory_;
    static ServiceConnectCallbackFactory *serviceConnectCallbackFactory_;
    static ServiceWriteCallbackFactory *serviceWriteCallbackFactory_;
    static ServiceReadCallbackFactory *serviceReadCallbackFactory_;
    static bool initialized_;
    static std::map<uint64_t, ::org::labcrypto::hottentot::runtime::Response*> responses_;
  };
}
}
}
}
}

#endif