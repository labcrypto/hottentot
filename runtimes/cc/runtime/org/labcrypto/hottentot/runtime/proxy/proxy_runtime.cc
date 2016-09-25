/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
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

#ifndef _MSC_VER
#include <signal.h>
#include <unistd.h>
#endif
 
#include "proxy_runtime.h"
#include "service_connector.h"
#include "plain_blocking_tcp_service_connector_factory.h"
#include "plain_service_connect_callback_factory.h"
#include "plain_service_write_callback_factory.h"
#include "plain_service_read_callback_factory.h"

#include "../configuration.h"
#include "../protocol_v1.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace proxy {
  ::org::labcrypto::hottentot::runtime::ProtocolFactory* ProxyRuntime::protocolFactory_ = NULL;
  ServiceConnectorFactory* ProxyRuntime::serviceConnectorFactory_ = NULL;
  ServiceConnectCallbackFactory* ProxyRuntime::serviceConnectCallbackFactory_ = NULL;
  ServiceWriteCallbackFactory* ProxyRuntime::serviceWriteCallbackFactory_ = NULL;
  ServiceReadCallbackFactory* ProxyRuntime::serviceReadCallbackFactory_ = NULL;
  bool ProxyRuntime::initialized_ = false;
  std::map<uint64_t, ::org::labcrypto::hottentot::runtime::Response*> ProxyRuntime::responses_;
  void
  ProxyRuntime::Init (
    int argc,
    char **argv
  ) {
    if (initialized_) {
      return;
    }
    Configuration::Init(argc, argv);
#ifndef _MSC_VER
    signal(SIGPIPE, SIG_IGN);
#endif
    ProxyRuntime::initialized_ = true;
  }
  void
  ProxyRuntime::Shutdown() {
    if (!initialized_) {
      return;
    }
    if (serviceConnectorFactory_) {
      delete serviceConnectorFactory_;
    }
    initialized_ = false;
  }
  ::org::labcrypto::hottentot::runtime::ProtocolFactory*
  ProxyRuntime::GetProtocolFactory() {
    if (protocolFactory_ == NULL) {
      protocolFactory_ = new ::org::labcrypto::hottentot::runtime::ProtocolV1Factory;
    }
    return protocolFactory_;
  }
  ServiceConnectorFactory*
  ProxyRuntime::GetServiceConnectorFactory() {
    if (serviceConnectorFactory_ == NULL) {
      serviceConnectorFactory_ = new PlainBlockingTcpServiceConnectorFactory;
    }
    return serviceConnectorFactory_;
  }
  ServiceConnectCallbackFactory*
  ProxyRuntime::GetServiceConnectCallbackFactory() {
    if (serviceConnectCallbackFactory_ == NULL) {
      serviceConnectCallbackFactory_ = new PlainServiceConnectCallbackFactory;
    }
    return serviceConnectCallbackFactory_;
  }
  ServiceWriteCallbackFactory*
  ProxyRuntime::GetServiceWriteCallbackFactory() {
    if (serviceWriteCallbackFactory_ == NULL) {
      serviceWriteCallbackFactory_ = new PlainServiceWriteCallbackFactory;
    }
    return serviceWriteCallbackFactory_;
  }
  ServiceReadCallbackFactory*
  ProxyRuntime::GetServiceReadCallbackFactory() {
    if (serviceReadCallbackFactory_ == NULL) {
      serviceReadCallbackFactory_ = new PlainServiceReadCallbackFactory;
    }
    return serviceReadCallbackFactory_;
  }
}
}
}
}
}