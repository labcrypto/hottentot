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
 
#include <iostream>
#include <stdint.h>

#include "default_request_callback.h"
#include "request_handler.h"

#include "../response.h"
#include "../request.h"
#include "../logger.h"
#include "../utils.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        Response*
        DefaultRequestCallback::OnRequest(void *source,
                                          Request &request) {
          ::naeem::hottentot::runtime::Logger::GetOut() << "A new request is received." << std::endl;
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