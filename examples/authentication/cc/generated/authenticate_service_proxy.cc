#include "authenticate_service_proxy.h"
#include "token.h"

namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        Token*
        AuthenticateServiceProxy::Authenticate(Credential *credential) {
          // TODO(kamran) Make request
          // TODO(kamran) Serailize request
          // TODO(kamran) Connect to server
          // TODO(kamran) Send request byte array
          // TODO(kamran) Read response byte array
          // TODO(kamran) Deserialize response byte array
          // TODO(kamran) Return response
          Token *t = new Token;
          t->SetValue("1iu3hdabsdmg");
          return t;
        }
      }
    }
  }
}