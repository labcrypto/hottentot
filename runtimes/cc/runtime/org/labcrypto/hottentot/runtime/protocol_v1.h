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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__PROTOCOL_V1_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__PROTOCOL_V1_H_

#include <vector>

#include "protocol.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
  class _Argument {
  public:
    unsigned char *data_;
    uint32_t dataLength_;
  };
  class RequestV1 : public Request {
  public:
    enum RequestType {
      Unknown,
      ServiceListQuery,
      InvokeStateless
    };
  public:
    RequestV1()
      : argumentCount_(0) {
    }
    ~RequestV1() {
      for (uint32_t i = 0; i < args_.size(); i++) {
        delete [] args_[i].data_;
      }
    }
    inline RequestType GetType() const {
      return type_;
    }
    inline void SetType(RequestType type) {
      type_ = type;
    }
    inline uint32_t GetMethodId() const {
      return methodId_;
    }
    inline void SetMethodId(uint32_t methodId) {
      methodId_ = methodId;
    }
    inline uint32_t GetArgumentCount() const {
      return argumentCount_;
    }
    inline void SetArgumentCount(uint32_t argumentCount) {
      argumentCount_ = argumentCount;
    }
    inline void AddArgument(unsigned char *data, uint32_t dataLength) {
      _Argument argument;
      argument.data_ = data;
      argument.dataLength_ = dataLength;
      args_.push_back(argument);
      argumentCount_++;
    }
    inline unsigned char* GetArgumentData(uint8_t index) {
      return args_[index].data_;
    }
    inline uint32_t GetArgumentLength(uint8_t index) {
      return args_[index].dataLength_;
    }
  private:
    RequestType type_;
    uint32_t methodId_;
    uint32_t argumentCount_;
    std::vector<_Argument> args_;
  };
  class ResponseV1 : public Response {
  public:
    ResponseV1() {
    }
    virtual ~ResponseV1() {
      if (data_) {
        delete [] data_;
      }
    }
  public:
    inline unsigned char* GetData() const {
      return data_;
    }
    inline void SetData(unsigned char *data) {
      data_ = data;
    }
    inline uint32_t GetDataLength() const {
      return dataLength_;
    }
    inline void SetDataLength(uint32_t dataLength) {
      dataLength_ = dataLength;
    }
  private:
    /*
     * Success = 0
     * Fault > 0
     */
    unsigned char *data_;
    uint32_t dataLength_;
  };
  class ProtocolV1 : public Protocol {
  enum State {
    ReadingLengthState,
    ReadingDataState
  };
  public:
    ProtocolV1();
    virtual ~ProtocolV1();
  public:
    virtual unsigned char* SerializeRequest (
      Request *,
      uint32_t *
    );
    virtual unsigned char* SerializeResponse (
      Response *,
      uint32_t *
    );
    virtual Request* DeserializeRequest (
      unsigned char *,
      uint32_t
    );
    virtual Response* DeserializeResponse (
      unsigned char *,
      uint32_t
    );
  public:
    virtual void FeedRequestData (
      unsigned char *,
      uint32_t
    );
    virtual void FeedResponseData (
      unsigned char *,
      uint32_t
    );
  public:
    // virtual bool IsResponseComplete();
    // virtual Response* GetResponse();
  private:
    // bool isResponseComplete_;
    // Response *response_;
  private:
    uint32_t readingLength_;
    uint32_t readingCounter_;
    uint32_t targetCounter_;
    std::vector<unsigned char> readingBuffer_;
    State currentState_;
  };
}
}
}
}

#endif