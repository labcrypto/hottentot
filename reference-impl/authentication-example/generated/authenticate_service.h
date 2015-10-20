#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_H_

#include <stdint.h>

#include <string>

#include "token.h"
#include "credential.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class AuthenticateService {
        public:
          virtual Token& Authenticate(Credential &) = 0;
        };
      }
    }
  }
}
#endif