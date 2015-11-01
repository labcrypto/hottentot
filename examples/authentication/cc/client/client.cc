#include <iostream>

#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>

#include "../generated/token.h"
#include "../generated/credential.h"
#include "../generated/authenticate_service.h"
#include "../generated/proxy/authenticate_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    ::naeem::hottentot::examples::auth::AuthenticateService *proxy = 
        ::naeem::hottentot::examples::auth::proxy::AuthenticateServiceProxyBuilder::Create("127.0.0.1", 2000);
    ::naeem::hottentot::examples::auth::Credential credential;
    credential.SetUsername("Admin");
    credential.SetPassword("12345");
    ::naeem::hottentot::examples::auth::Token *token = 
        proxy->Authenticate(&credential);
    std::cout << "Token: " << token->GetValue() << std::endl;
    ::naeem::hottentot::examples::auth::proxy::AuthenticateServiceProxyBuilder::Destroy(proxy);
    delete token;
  } catch (...) {
    std::cout << "Error." << std::endl;
  }
  return 0;
}