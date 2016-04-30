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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_SERVICE__ENDPOINT_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_SERVICE__ENDPOINT_H_

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
namespace service {
  // TODO(kamran) We need different endpoints for IPv4 and IPv6.
  class Endpoint {
  public:
    class Comparator {
    public:
      bool operator()(const Endpoint &left, const Endpoint &right) const {
        if (left.host_.compare(right.host_) < 0) {
          return true;
        }
        return left.port_ < right.port_;
      }
    };
    class Comparator2 {
    public:
      bool operator()(const Endpoint &left, const Endpoint &right) const {
        return left.host_.compare(right.host_) < 0 && left.port_ < right.port_;
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
  public:
    inline Endpoint& operator =(const Endpoint& other) {
      host_ = other.host_;
      port_ = other.port_;
      return *this;
    }
  private:
    std::string host_;
    uint32_t port_;
  };
}
}
}
}
}

#endif