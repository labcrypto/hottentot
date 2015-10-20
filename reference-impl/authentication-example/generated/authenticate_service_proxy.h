#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_PROXY_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_PROXY_H_

#include <stdint.h>

#include <string>

#include "token.h"
#include "credential.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class AuthenticateServiceProxy : public AuthenticateService, 
                                         public ::naeem::hottentot::runtime::proxy::Proxy {
        public:
          AuthenticateServiceProxy();
          virtual ~AuthenticateServiceProxy();
        public:
          virtual Token& Authenticate(Credential &) override;
        };
      }
    }
  }
}
#endif