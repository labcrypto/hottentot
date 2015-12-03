/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 03-12-2015 11:50:27
 * Name: calculator_service_proxy_builder.h
 * Description:
 *   This file contains definition of the proxy builder class.
 ******************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__PROXY__CALCULATOR_SERVICE_PROXY_BUILDER_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__PROXY__CALCULATOR_SERVICE_PROXY_BUILDER_H_

#include <stdint.h>
#include <string>


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {
class CalculatorService;
namespace proxy {
  class CalculatorServiceProxyBuilder {
  public:
    static CalculatorService* Create(std::string /* host */, uint32_t /* port */);
    static void Destroy(CalculatorService *);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif