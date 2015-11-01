#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__ABSTRACT_AUTHENTICATE_SERVICE_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__ABSTRACT_AUTHENTICATE_SERVICE_H_

#include <stdint.h>

#include <string>

#include <naeem/hottentot/runtime/service/service.h>

#include "../token.h"
#include "../credential.h"
#include "../authenticate_service.h"
#include "authenticate_service_request_handler.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        namespace service {
          class AbstractAuthenticateService : public AuthenticateService,
                                              public ::naeem::hottentot::runtime::service::Service {
          public:
            inline virtual uint8_t GetServiceId() const {
              return 1;
            }
          protected:
            inline virtual ::naeem::hottentot::runtime::service:: RequestHandler* MakeRequestHandler() {
              return new AuthenticateServiceRequestHandler(this);
            }
          };
        }
      }
    }
  }
}

#endif