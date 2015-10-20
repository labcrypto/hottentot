#include <iostream>

#include <naeem/hottentot/runtime/service/htn_runtime.h>

#include "../generated/token.h"
#include "../generated/credential.h"
#include "../generated/authenticate_service.h"

#include "authenticate_service_impl.h"


int
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::examples::auth::AuthenticateServiceImpl *authenticateService =
        new ::naeem::hottentot::examples::auth::AuthenticateServiceImpl();
    ::naeem::hottentot::runtime::service::HtnRuntime::Register("0.0.0.0", 2000, authenticateService);
    ::naeem::hottentot::runtime::service::HtnRuntime::Start();
  } catch (...) {
    std::cout << "Error." << std::endl;
  }
  return 0;
}