/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 05-02-2016 09:34:46
 * Name: authenticate_service_impl.cc
 * Description:
 *   This file contains empty implementation of sample stub.
 ******************************************************************/
 
#include <naeem/hottentot/runtime/configuration.h>
#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/utils.h>

#include "authenticate_service_impl.h"

#include "../credential.h"
#include "../user.h"
#include "../token.h"


namespace naeem {
namespace hottentot {
namespace examples {
namespace auth {
  void
  AuthenticateServiceImpl::OnInit() {
    // TODO: Called when service is initializing.
  }
  void
  AuthenticateServiceImpl::OnShutdown() {
    // TODO: Called when service is shutting down.
  }
  void
  AuthenticateServiceImpl::Authenticate(::naeem::hottentot::examples::auth::Credential &credential, ::naeem::hottentot::examples::auth::Token &out) {
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "AuthenticateServiceImpl::Authenticate() is called." << std::endl;
    }
    out.SetValue("Asdlhih34ou23riuwhfkhsdljf");
  }
} // END OF NAMESPACE auth
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE naeem