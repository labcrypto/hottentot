#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_IMPL_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_IMPL_H_

#include <stdint.h>
#include <string>

#include "../generated/service/abstract_authenticate_service.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class Token;
        class Credential;
        class AuthenticateServiceImpl : public ::naeem::hottentot::examples::auth::service::AbstractAuthenticateService {
        public:
          AuthenticateServiceImpl() {}
          virtual ~AuthenticateServiceImpl() {}
        public:
          virtual Token* Authenticate(Credential *);
        };
      }
    }
  }
}

#endif