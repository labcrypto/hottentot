/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 10-02-2016 03:06:23
 * Name: calculator_service_proxy_builder.h
 * Description:
 *   This file contains definition of the proxy builder class.
 ******************************************************************/

#ifndef _EXAMPLE_GENERATED_ABC_XYZ__PROXY__CALCULATOR_SERVICE_PROXY_BUILDER_H_
#define _EXAMPLE_GENERATED_ABC_XYZ__PROXY__CALCULATOR_SERVICE_PROXY_BUILDER_H_

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <string>


namespace example {
namespace generated {
namespace abc {
namespace xyz {
namespace proxy {
class CalculatorService;
  class CalculatorServiceProxyBuilder {
  public:
    static CalculatorService* Create(std::string /* host */, uint32_t /* port */);
    static void Destroy(CalculatorService *);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE xyz
} // END OF NAMESPACE abc
} // END OF NAMESPACE generated
} // END OF NAMESPACE example

#endif