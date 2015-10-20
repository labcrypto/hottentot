#include "authenticate_service_proxy_builder.h"
#include "authenticate_service_proxy.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        AuthenticateService*
        AuthenticateServiceProxyBuilder::CreateAuthenticateServiceProxy(std::string host,
                                                                        uint32_t port) {
          // TODO Connect to server
          // TODO Obtain a connection fro Authentication service
          return new AuthenticateServiceProxy(/* ... */);
        }
      }
    }
  }
}