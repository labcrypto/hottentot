#include "authenticate_service_impl.h"

#include "../generated/token.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        Token*
        AuthenticateServiceImpl::Authenticate(Credential *credential) {
          Token *token = new Token;
          token->SetValue("ads13kjadlks");
          return token;
        }
      }
    }
  }
}