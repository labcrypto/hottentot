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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_RUNTIME_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_RUNTIME_H_

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

#include "endpoint.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class Service;
        class RequestHandler;
        class TcpServerFactory;
        class ServiceRuntime {
        public:
          static void Init(int argc, char **argv);
          static void Shutdown();
          static void Register(std::string   /* host */, 
                               uint32_t      /* port */, 
                               Service *     /* service implementation */);
          static void Start();
          static TcpServerFactory* GetTcpServerFactory();
          inline static void SetTcpServerFactory(TcpServerFactory *tcpServerFactory) {
            tcpServerFactory_ = tcpServerFactory;
          }
          inline static bool Verbose() {
            return verbose_;
          }
        private:
          static bool verbose_;
          static TcpServerFactory *tcpServerFactory_;
          static std::map<Endpoint, std::vector<Service*>*, Endpoint::Comparator> services_;
          static std::map<Endpoint, std::map<uint8_t, RequestHandler*>*, Endpoint::Comparator> requestHandlers_;
        };
      }
    }
  }
}

#endif