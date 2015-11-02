#include <string.h>

#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/response.h>

#include "authenticate_service_request_handler.h"
#include "abstract_authenticate_service.h"
#include "../credential.h"
#include "../authenticate_service.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        namespace service {
          void 
          AuthenticateServiceRequestHandler::HandleRequest(::naeem::hottentot::runtime::Request &request,
                                                           ::naeem::hottentot::runtime::Response &response) {
            if (request.GetMethodId() == 1) {
              ::naeem::hottentot::examples::auth::Credential credential;
              credential.Deserialize(request.GetArgumentData(0), request.GetArgumentDataLength(0));
              ::naeem::hottentot::examples::auth::service::AbstractAuthenticateService *authenticateService = 
                dynamic_cast<naeem::hottentot::examples::auth::service::AbstractAuthenticateService*>(service_);
              Token *token = authenticateService->Authenticate(&credential);
              uint32_t tokenSerializedDataLength = 0;
              unsigned char *tokenSerializedData = token->Serialize(&tokenSerializedDataLength);
              response.SetStatusCode(0);
              response.SetData(tokenSerializedData);
              response.SetDataLength(tokenSerializedDataLength);
              return;
            }
            char errorMessage[] = "Method not found.";
            response.SetStatusCode(1);
            response.SetData((unsigned char*)errorMessage);
            response.SetDataLength(strlen(errorMessage));
          }
        }
      }
    }
  }
}