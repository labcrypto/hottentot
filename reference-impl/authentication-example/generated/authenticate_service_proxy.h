#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_PROXY_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_PROXY_H_

#include <stdint.h>

#include <string>

#include <naeem/hottentot/runtime/proxy/proxy.h>

#include "authenticate_service.h"
#include "token.h"
#include "credential.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class AuthenticateServiceProxy : public AuthenticateService, 
                                         public ::naeem::hottentot::runtime::proxy::Proxy {
        public:
          AuthenticateServiceProxy() {}
          virtual ~AuthenticateServiceProxy() {}
        public:
          virtual Token* Authenticate(Credential *);
        };
      }
    }
  }
}
#endif