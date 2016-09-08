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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__PROTOCOL_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__PROTOCOL_H_

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
  class Protocol;
  class Request {
  protected:
    Request() {   
    }
  public:
    inline uint32_t GetServiceId() const {
      return serviceId_;
    }
    inline void SetServiceId(uint32_t serviceId) {
      serviceId_ = serviceId;
    }
  protected:
    uint32_t serviceId_;
  };
  class Response {
  protected:
    Response()
      : statusCode_(0) {
    }
  public:
    uint16_t
    GetStatusCode() {
      return statusCode_;
    }
    void
    SetStatusCode(uint16_t statusCode) {
      statusCode_ = statusCode;
    }
  protected:
    uint16_t statusCode_;
  };
  class RequestCallback {
  public:
    RequestCallback () {
    }
    virtual ~RequestCallback() {
    }
  public:
    virtual void OnRequest (
      Protocol *,
      Request *
    ) = 0;
  };
  class ResponseCallback {
  public:
    ResponseCallback ()
      : response_(NULL),
        responseProcessed_(false) {
    }
    virtual ~ResponseCallback() {
    }
  public:
    bool
    IsResponseProcessed() {
      return responseProcessed_;
    }
    Response*
    GetResponse() {
      return response_;
    }
  public:
    virtual void OnResponse (
      Protocol *,
      Response *
    ) = 0;
  protected:
    Response *response_;
    bool responseProcessed_;
    uint16_t statusCode_;
  };
  class Protocol {
  public:
    /* Protocol(int remoteSocketFD) 
      : remoteSocketFD_(remoteSocketFD) {
    } */
    Protocol() 
      : requestCallback_(NULL),
        responseCallback_(NULL) {
    }
    virtual ~Protocol() {
    }
  public:
    virtual unsigned char* SerializeRequest (
      Request *, 
      uint32_t *
    ) = 0;
    virtual unsigned char* SerializeResponse (
      Response *,
      uint32_t *
    ) = 0;
    virtual Request* DeserializeRequest (
      unsigned char *,
      uint32_t
    ) = 0;
    virtual Response* DeserializeResponse (
      unsigned char *,
      uint32_t
    ) = 0;
  public:
    virtual void SetRequestCallback (
      RequestCallback *requestCallback
    ) {
      requestCallback_ = requestCallback;
    }
    virtual void SetResponseCallback (
      ResponseCallback *responseCallback
    ) {
      responseCallback_ = responseCallback;
    }
  public:
    virtual void FeedRequestData (
      unsigned char *,
      uint32_t
    ) = 0;
    virtual void FeedResponseData (
      unsigned char *,
      uint32_t
    ) = 0;
  public:
    /* virtual bool IsResponseComplete() = 0;
    virtual Response* GetResponse() = 0; */
  protected:
    // int remoteSocketFD_;
    RequestCallback *requestCallback_;
    ResponseCallback *responseCallback_;
  };
}
}
}
}

#endif