#include <iostream>

#include <naeem/hottentot/runtime/service/service_runtime.h>

#include "../generated/token.h"
#include "../generated/credential.h"
#include "../generated/authenticate_service.h"

#include "authenticate_service_impl.h"


int
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::service::ServiceRuntime::Init(argc, argv);
    ::naeem::hottentot::examples::auth::AuthenticateServiceImpl *authenticateService =
        new ::naeem::hottentot::examples::auth::AuthenticateServiceImpl();
    ::naeem::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2000, authenticateService);
    ::naeem::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2001, authenticateService);
    ::naeem::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2002, authenticateService);
    ::naeem::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2002, authenticateService);
    ::naeem::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2004, authenticateService);
    ::naeem::hottentot::runtime::service::ServiceRuntime::Start();
  } catch (...) {
    std::cout << "Error." << std::endl;
  }
  return 0;
}
