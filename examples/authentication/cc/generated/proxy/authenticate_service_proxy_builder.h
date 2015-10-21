#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__PROXY__AUTHENTICATE_SERVICE_PROXY_BUILDER_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__PROXY__AUTHENTICATE_SERVICE_PROXY_BUILDER_H_

#include <stdint.h>

#include <string>


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class AuthenticateService;
        namespace proxy {          
          class AuthenticateServiceProxyBuilder {
          public:
            static AuthenticateService* Create(std::string    /* host */,
                                               uint32_t       /* port */);
            static void Destroy(AuthenticateService *);
          };
        }
      }
    }
  }
}

#endif