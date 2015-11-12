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
 
#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__ABSTRACT_AUTHENTICATE_SERVICE_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__ABSTRACT_AUTHENTICATE_SERVICE_H_

#include <stdint.h>

#include <string>

#include <naeem/hottentot/runtime/service/service.h>

#include "../token.h"
#include "../credential.h"
#include "../authenticate_service.h"
#include "authenticate_service_request_handler.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        namespace service {
          class AbstractAuthenticateService : public AuthenticateService,
                                              public ::naeem::hottentot::runtime::service::Service {
          public:
            inline virtual uint8_t GetServiceId() const {
              return 1;
            }
          protected:
            inline virtual ::naeem::hottentot::runtime::service:: RequestHandler* MakeRequestHandler() {
              return new AuthenticateServiceRequestHandler(this);
            }
          };
        }
      }
    }
  }
}

#endif