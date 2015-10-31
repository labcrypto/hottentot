#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__REQUEST_CALLBACK_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__REQUEST_CALLBACK_H_

#include <map>
#include <stdint.h>

namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class Request;
        class Response;
        class RequestHandler;
        class RequestCallback {
        public:
          RequestCallback(std::map<uint8_t, RequestHandler*> *requestHandlers)
            : requestHandlers_(requestHandlers) {
          }
          virtual ~RequestCallback() {}
        public:
          virtual Response* OnRequest(void *     /* Source */,
                                      Request &  /* Request object */) = 0;
        protected:
          std::map<uint8_t, RequestHandler*> *requestHandlers_;
        };
      }
    }
  }
}

#endif