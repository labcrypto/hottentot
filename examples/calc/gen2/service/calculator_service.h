/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 05:11:23
 * Name: calculator_service.h
 * Description:
 *   This file contains definition of service interface.
 ***************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__CALCULATOR_SERVICE_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__CALCULATOR_SERVICE_H_

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

#include <org/labcrypto/hottentot/primitives.h>
#include <org/labcrypto/hottentot/runtime/service/hot_context.h>




namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {
namespace service {
  class CalculatorService {
  public:
     CalculatorService() {}
     virtual ~CalculatorService() {}
  public:
    virtual void Add(
      ::org::labcrypto::hottentot::UInt16 &a, 
      ::org::labcrypto::hottentot::UInt16 &b, 
      ::org::labcrypto::hottentot::UInt16 &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    ) = 0;
    virtual void Mul(
      ::org::labcrypto::hottentot::Int16 &a, 
      ::org::labcrypto::hottentot::Int16 &b, 
      ::org::labcrypto::hottentot::Int16 &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    ) = 0;
  };
} // END OF NAMESPACE service
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif