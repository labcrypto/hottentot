/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 03-12-2015 11:21:04
 * Name: calculator_service_client.h
 * Description:
 *   This file contains a sample client.
 ******************************************************************/

#include <iostream>

#include <naeem/hottentot/runtime/logger.h>
 #include <naeem/hottentot/runtime/types/primitives.h>
#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>


#include "../calculator_service.h"
#include "../proxy/calculator_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::Logger::Init();
    std::cout << "Logger is initialized." << std::endl;
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    std::cout << "Proxy runtime is initialized." << std::endl;
    ::ir::ntnaeem::hottentot::examples::calc::CalculatorService *proxy = 
        ::ir::ntnaeem::hottentot::examples::calc::proxy::CalculatorServiceProxyBuilder::Create("127.0.0.1", 2000);
    std::cout << "Proxy object is created." << std::endl;
    ::naeem::hottentot::runtime::types::UInt16 a(3);
    ::naeem::hottentot::runtime::types::UInt16 b(4);
    ::naeem::hottentot::runtime::types::UInt16 res = proxy->Add(a, b);
    std::cout << "Result is " << res.GetValue() << std::endl;
    ::ir::ntnaeem::hottentot::examples::calc::proxy::CalculatorServiceProxyBuilder::Destroy(proxy);
    std::cout << "Proxy object is destroyed." << std::endl;
    // Delete allocated objects
  } catch (...) {
    std::cout << "Error." << std::endl;
    return 1;
  }
  return 0;
}
