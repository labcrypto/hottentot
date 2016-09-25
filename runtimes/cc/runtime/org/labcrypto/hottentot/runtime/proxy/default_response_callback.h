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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_PROXY__DEFAULT_RESPONSE_CALLBACK_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_PROXY__DEFAULT_RESPONSE_CALLBACK_H_

#include "../protocol.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
  class Request;
namespace proxy {
  class ServiceIO;
  class DefaultResponseCallback : public ::org::labcrypto::hottentot::runtime::ResponseCallback {
  public:
    DefaultResponseCallback (
      ServiceIO *serviceIO,
      ::org::labcrypto::hottentot::runtime::Request *request
    ) : serviceIO_(serviceIO),
        request_(request) {
    }
    virtual ~DefaultResponseCallback() {}
  public:
    virtual void OnResponse (
      ::org::labcrypto::hottentot::runtime::Protocol *,
      ::org::labcrypto::hottentot::runtime::Response *
    );
  private:
    ServiceIO *serviceIO_;
    ::org::labcrypto::hottentot::runtime::Request *request_;
  };
}
}
}
}
}

#endif