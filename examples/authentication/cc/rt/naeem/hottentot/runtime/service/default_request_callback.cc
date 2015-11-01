#include <iostream>

#include "default_request_callback.h"
#include "request_handler.h"
#include "../response.h"
#include "../request.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        Response*
        DefaultRequestCallback::OnRequest(void *source,
                                          Request &request) {
          if (requestHandlers_->count(request.GetServiceId()) > 0) {
            Response *response = new Response;
            RequestHandler *requestHandler = requestHandlers_->find(request.GetServiceId())->second;
            if (requestHandler == 0) {
              return 0;
            }
            requestHandler->HandleRequest(request, *response);
            return response;
          } else {
            return 0;            
          }
        }
      }
    }
  }
}