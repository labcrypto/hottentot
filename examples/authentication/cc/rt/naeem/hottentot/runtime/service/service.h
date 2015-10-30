#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class RequestHandler;
        class Service {
        public:
          Service() 
            : requestHandler_(0) {
          }
          virtual ~Service() {}
        public:
          virtual uint8_t GetServiceId() const = 0;
          virtual RequestHandler* GetRequestHandler() {
            if (requestHandler_ == 0) {
              MakeRequestHandler();
            }
            return requestHandler_;
          }
        protected:
          virtual RequestHandler* MakeRequestHandler() = 0;
        protected:
          RequestHandler *requestHandler_;
        };
      }
    }
  }
}

#endif