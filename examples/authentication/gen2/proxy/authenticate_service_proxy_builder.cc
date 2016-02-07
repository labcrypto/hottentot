/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 06-02-2016 03:48:37
 * Name: authenticate_service_proxy_builder.cc
 * Description:
 *   This file contains implementation of the proxy builder class.
 ******************************************************************/

#include "authenticate_service_proxy_builder.h"
#include "authenticate_service_proxy.h"


namespace naeem {
namespace hottentot {
namespace examples {
namespace auth {
namespace proxy {
  AuthenticateService*
  AuthenticateServiceProxyBuilder::Create(std::string host, uint32_t port) {
    return new AuthenticateServiceProxy(host, port);
  }
  void
  AuthenticateServiceProxyBuilder::Destroy(AuthenticateService *service) {
    delete service;
  }
} // END OF NAMESPACE proxy
} // END OF NAMESPACE auth
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE naeem