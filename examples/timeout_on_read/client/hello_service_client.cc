/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 24-03-2016 11:14:24
 * Name: hello_service_client.h
 * Description:
 *   This file contains a sample client.
 ******************************************************************/

#include <iostream>

#include <naeem/hottentot/runtime/configuration.h>
#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>


#include "../hotgen/proxy/hello_service.h"
#include "../hotgen/proxy/hello_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::Logger::Init();  
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy runtime is initialized." << std::endl;
    }
    ::ir::ntnaeem::hottentot::examples::timeout_on_read::proxy::HelloService *proxy = 
      ::ir::ntnaeem::hottentot::examples::timeout_on_read::proxy::HelloServiceProxyBuilder::Create("127.0.0.1", 2000);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy object is created." << std::endl;
    }
    try {
      ::naeem::hottentot::runtime::types::Utf8String name("Kamran");
      ::naeem::hottentot::runtime::types::Utf8String result;
      proxy->SayHelloTo(name, result);
      std::cout << "Results is: '" << result << "'" << std::endl;
    } catch (std::runtime_error &e) {
      ::naeem::hottentot::runtime::Logger::GetError() << e.what() << std::endl;
    }
    ::ir::ntnaeem::hottentot::examples::timeout_on_read::proxy::HelloServiceProxyBuilder::Destroy(proxy);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy object is destroyed." << std::endl;
    }
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Shutdown();
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy runtime is shutdown." << std::endl;
    }
    ::naeem::hottentot::runtime::Logger::Shutdown();  
  } catch (std::exception &e) {
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Shutdown();
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy runtime is shutdown." << std::endl;
    }
    ::naeem::hottentot::runtime::Logger::Shutdown();  
    ::naeem::hottentot::runtime::Logger::GetError() << e.what() << std::endl;
    return 1;
  } catch (...) {
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Shutdown();
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy runtime is shutdown." << std::endl;
    }
    ::naeem::hottentot::runtime::Logger::Shutdown();  
    ::naeem::hottentot::runtime::Logger::GetError() << "Error." << std::endl;
    return 1;
  }
  return 0;
}
