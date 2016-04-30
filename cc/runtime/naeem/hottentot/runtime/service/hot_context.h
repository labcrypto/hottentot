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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__HOT_CONTEXT_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__HOT_CONTEXT_H_

#include <string>


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace service {
  class HotContext {
  public:
    HotContext()
      : responseStatusCode_(0),
        faultMessage_("Fault Occurred.") {
    }
    ~HotContext() {
    }
  public:
    inline uint8_t GetResponseStatusCode() const {
      return responseStatusCode_;
    }
    inline void SetResponseStatusCode(uint8_t responseStatusCode) {
      responseStatusCode_ = responseStatusCode;
    }
    inline std::string& GetFaultMessage() {
      return faultMessage_;
    }
    inline void SetFaultMessage(std::string &faultMessage) {
      faultMessage_ = faultMessage;
    }
  public:
    inline void SetFaultyResponse(std::string faultMessage, uint8_t responseStatusCode = 50) {
      responseStatusCode_ = responseStatusCode;
      faultMessage_ = faultMessage;
    }
  private:
    uint8_t responseStatusCode_;
    std::string faultMessage_;
  };
}
}
}
}
}

#endif