#include <naeem/hottentot/runtime/utils.h>

#include "authenticate_service_impl.h"

#include "../generated/token.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        Token*
        AuthenticateServiceImpl::Authenticate(Credential *credential) {
          ::naeem::hottentot::runtime::Logger::GetOut() << "Implementation is called." << std::endl;
          Token *token = new Token;
          token->SetValue("ads13kjadlks");
          return token;
        }
      }
    }
  }
}