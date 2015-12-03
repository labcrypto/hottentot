/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 04-12-2015 02:07:30
 * Name: calculator_service_proxy.h
 * Description:
 *   This file contains definition of the proxy class.
 ***************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__PROXY__CALCULATOR_SERVICE_PROXY_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__PROXY__CALCULATOR_SERVICE_PROXY_H_

#include <stdint.h>
#include <string>

#include <naeem/hottentot/runtime/types/primitives.h>
#include <naeem/hottentot/runtime/proxy/proxy.h>

#include "../calculator_service.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {

namespace proxy {
  class CalculatorServiceProxy : public ::ir::ntnaeem::hottentot::examples::calc::CalculatorService, 
    public ::naeem::hottentot::runtime::proxy::Proxy {
  public:
    CalculatorServiceProxy(std::string host, uint32_t port) 
      : ::naeem::hottentot::runtime::proxy::Proxy(host, port) {}
    virtual ~CalculatorServiceProxy() {}
  public:
::naeem::hottentot::runtime::types::UInt16 Add(::naeem::hottentot::runtime::types::UInt16 a, ::naeem::hottentot::runtime::types::UInt16 b);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif