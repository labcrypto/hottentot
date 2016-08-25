/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 26-08-2016 12:28:27
 * Name: echo_service_client.h
 * Description:
 *   This file contains a sample client.
 ******************************************************************/

#include <iostream>

#include <org/labcrypto/hottentot/runtime/configuration.h>
#include <org/labcrypto/hottentot/runtime/logger.h>
#include <org/labcrypto/hottentot/runtime/utils.h>
#include <org/labcrypto/hottentot/runtime/proxy/proxy_runtime.h>

#include "../request_message.h"
#include "../response_message.h"
#include "../proxy/echo_service.h"
#include "../proxy/echo_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::org::labcrypto::hottentot::runtime::Logger::Init();  
    ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " << 
          "Proxy runtime is initialized." << std::endl;
    }
    ::ir::ntnaeem::hottentot::examples::echoer::proxy::EchoService *proxy = 
      ::ir::ntnaeem::hottentot::examples::echoer::proxy::EchoServiceProxyBuilder::Create("127.0.0.1", 2000);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " << 
          "Proxy object is created." << std::endl;
    }
    try {
      // ====================================================
      // TODO: Do whatever you want with proxy objects.
      // TODO: Delete allocated objects
      // ====================================================
    } catch (std::runtime_error &e) {
      ::org::labcrypto::hottentot::runtime::Logger::GetError() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " << 
          e.what() << std::endl;
    }
    ::ir::ntnaeem::hottentot::examples::echoer::proxy::EchoServiceProxyBuilder::Destroy(proxy);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Proxy object is destroyed." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::Shutdown();
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Proxy runtime is shutdown." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Logger::Shutdown();  
  } catch (std::exception &e) {
    ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::Shutdown();
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Proxy runtime is shutdown." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Logger::Shutdown();  
    ::org::labcrypto::hottentot::runtime::Logger::GetError() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          e.what() << std::endl;
    return 1;
  } catch (...) {
    ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::Shutdown();
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<
          "Proxy runtime is shutdown." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Logger::Shutdown();  
    ::org::labcrypto::hottentot::runtime::Logger::GetError() << 
        "[" << ::org::labcrypto::hottentot::runtime::Utils::GetCurrentUTCTimeString() << "]: " <<           "Error." << std::endl;
    return 1;
  }
  return 0;
}