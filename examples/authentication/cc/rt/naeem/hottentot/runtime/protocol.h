#ifndef _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_H_
#define _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_H_

#include <stdint.h>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class RequestCallback;
      }
      namespace proxy {
        class ResponseCallback;
      }
      class Request;
      class Response;
      class Protocol {
      public:
        virtual unsigned char* SerializeRequest(Request *      /* Request object*/, 
                                                uint32_t *     /* Length */) = 0;
        virtual unsigned char* SerializeResponse(Response *    /* Response object*/, 
                                                 uint32_t *    /* Length */) = 0;
        virtual Response* DeserializeRequest(unsigned char *   /* Request data */, 
                                             uint32_t          /* Request data length */) = 0;
        virtual Response* DeserializeResponse(unsigned char *  /* Response data */, 
                                              uint32_t         /* Response data length */) = 0;
      public:
        virtual void SetRequestCallback(::naeem::hottentot::runtime::service::RequestCallback *requestCallback) {
          requestCallback_ = requestCallback;
        }
        virtual void SetResponseCallback(::naeem::hottentot::runtime::proxy::ResponseCallback *responseCallback) {
          responseCallback_ = responseCallback;
        }
      public:
        virtual void ProcessDataForRequest(unsigned char *     /* Data chuck */,
                                           uint32_t            /* Data chunk length */) = 0;
        virtual void ProcessDataForResponse(unsigned char *    /* Data chuck */,
                                            uint32_t           /* Data chunk length */) = 0;
      protected:
        ::naeem::hottentot::runtime::service::RequestCallback *requestCallback_;
        ::naeem::hottentot::runtime::proxy::ResponseCallback *responseCallback_;
      };
    }
  }
}

#endif