#include "authenticate_service_proxy_builder.h"
#include "authenticate_service_proxy.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        namespace proxy {
          AuthenticateService*
          AuthenticateServiceProxyBuilder::Create(std::string host,
                                                  uint32_t port) {
            return new AuthenticateServiceProxy(host, port);
          }
          void
          AuthenticateServiceProxyBuilder::Destroy(AuthenticateService *authenticateService) {
            delete authenticateService;
          }
        }
      }
    }
  }
}