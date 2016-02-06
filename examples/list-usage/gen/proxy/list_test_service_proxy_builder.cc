/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 06-02-2016 03:43:41
 * Name: list_test_service_proxy_builder.cc
 * Description:
 *   This file contains implementation of the proxy builder class.
 ******************************************************************/

#include "list_test_service_proxy_builder.h"
#include "list_test_service_proxy.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace listtest {
namespace proxy {
  ListTestService*
  ListTestServiceProxyBuilder::Create(std::string host, uint32_t port) {
    return new ListTestServiceProxy(host, port);
  }
  void
  ListTestServiceProxyBuilder::Destroy(ListTestService *service) {
    delete service;
  }
} // END OF NAMESPACE proxy
} // END OF NAMESPACE listtest
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir