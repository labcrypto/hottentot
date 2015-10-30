#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__AUTHENTICATE_SERVICE_REQUEST_HANDLER_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__AUTHENTICATE_SERVICE_REQUEST_HANDLER_H_

#include <stdint.h>

#include <string>

#include <naeem/hottentot/runtime/service/request_handler.h>


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        namespace service {
          class AuthenticateServiceRequestHandler : public ::naeem::hottentot::runtime::service::RequestHandler {
          public:
            AuthenticateServiceRequestHandler(::naeem::hottentot::runtime::service::Service *service)
              : ::naeem::hottentot::runtime::service::RequestHandler(service) {
            }
            virtual ~AuthenticateServiceRequestHandler() {}
          public:
            virtual void HandleRequest(::naeem::hottentot::runtime::Request &   /* Request object */,
                                       ::naeem::hottentot::runtime::Response &  /* Response object */);
          };
        }
      }
    }
  }
}

#endif