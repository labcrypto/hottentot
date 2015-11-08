/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
 
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
              credential.Deserialize(request.GetArgumentData(0), request.GetArgumentLength(0));
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