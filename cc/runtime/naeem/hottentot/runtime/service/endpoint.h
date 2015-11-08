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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__ENDPOINT_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__ENDPOINT_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        // TODO(kamran) We need different endpoints for IPv4 and IPv6.
        class Endpoint {
        public:
          class Comparator {
          public:
            bool operator()(const Endpoint &left, const Endpoint &right) const {
              if (left.host_ < right.host_) {
                return true;
              }
              return left.port_ < right.port_;
            }
          };
        public:
          Endpoint(std::string host, uint32_t port) 
            : host_(host), port_(port) {
          }
          ~Endpoint() {}
        public:
          inline std::string GetHost() const {
            return host_;
          }
          inline void SetHost(std::string host) {
            host_ = host;
          }
          inline uint32_t GetPort() const {
            return port_;
          }
          inline void SetPort(uint32_t port) {
            port_ = port;
          }
          
        private:
          std::string host_;
          uint32_t port_;
        };
      }
    }
  }
}

#endif