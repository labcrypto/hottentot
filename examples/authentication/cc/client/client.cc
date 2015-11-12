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

#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>

#include "../generated/token.h"
#include "../generated/credential.h"
#include "../generated/authenticate_service.h"
#include "../generated/proxy/authenticate_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::Logger::Init();
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    ::naeem::hottentot::examples::auth::AuthenticateService *proxy = 
        ::naeem::hottentot::examples::auth::proxy::AuthenticateServiceProxyBuilder::Create("127.0.0.1", 2005);
    ::naeem::hottentot::examples::auth::Credential credential;
    credential.SetUsername("Admin");
    credential.SetPassword("12345");
    ::naeem::hottentot::examples::auth::Token *token = proxy->Authenticate(&credential);
    std::cout << "Token: " << token->GetValue() << std::endl;
    ::naeem::hottentot::examples::auth::proxy::AuthenticateServiceProxyBuilder::Destroy(proxy);
    delete token;
  } catch (...) {
    std::cout << "Error." << std::endl;
  }
  return 0;
}
