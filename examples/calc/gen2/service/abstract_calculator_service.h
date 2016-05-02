/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 05:11:23
 * Name: calculator_service.h
 * Description:
 *   This file contains definition of an abstract service class.
 ******************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__ABSTRACT_CALCULATOR_SERVICE_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__ABSTRACT_CALCULATOR_SERVICE_H_

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

#include <org/labcrypto/hottentot/runtime/service/service.h>



#include "calculator_service.h"
#include "calculator_service_request_handler.h"
#include "../enums.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {
namespace service {
  class AbstractCalculatorService : public CalculatorService, public ::org::labcrypto::hottentot::runtime::service::Service {
  public:
    AbstractCalculatorService() {}
    virtual ~AbstractCalculatorService() {}
  public:
    inline virtual uint32_t GetServiceId() const {
      return 2191962707;
    }
  protected:
    inline virtual ::org::labcrypto::hottentot::runtime::service::RequestHandler* MakeRequestHandler() {
      return new CalculatorServiceRequestHandler(this);
    }
  };
} // END OF NAMESPACE service
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif