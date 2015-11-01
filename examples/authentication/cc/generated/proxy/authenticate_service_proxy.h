#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__PROXY__AUTHENTICATE_SERVICE_PROXY_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__PROXY__AUTHENTICATE_SERVICE_PROXY_H_

#include <stdint.h>
#include <string>

#include <naeem/hottentot/runtime/proxy/proxy.h>

#include "../authenticate_service.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class Token;
        class Credential;
        namespace proxy {
          class AuthenticateServiceProxy : public ::naeem::hottentot::examples::auth::AuthenticateService, 
                                           public ::naeem::hottentot::runtime::proxy::Proxy {
          public:
            AuthenticateServiceProxy(std::string host, 
                                     uint32_t port) 
              : ::naeem::hottentot::runtime::proxy::Proxy(host, port) {}
            virtual ~AuthenticateServiceProxy() {}
          public:
            virtual Token* Authenticate(Credential *);
          };
        }
      }
    }
  }
}

#endif