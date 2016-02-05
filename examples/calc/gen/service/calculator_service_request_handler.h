/***********************************************************************
 * Generated by Hottentot CC Generator
 * Date: 05-02-2016 10:31:51
 * Name: calculator_service_request_handler.h
 * Description:
 *   This file contains definition of service's request handler class.
 ***********************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__CALCULATOR_SERVICE_REQUEST_HANDLER_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__CALCULATOR_SERVICE_REQUEST_HANDLER_H_

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

#include <naeem/hottentot/runtime/service/request_handler.h>


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {
namespace service {
  class CalculatorServiceRequestHandler : public ::naeem::hottentot::runtime::service::RequestHandler {
  public:
    CalculatorServiceRequestHandler(::naeem::hottentot::runtime::service::Service *service)
      : ::naeem::hottentot::runtime::service::RequestHandler(service) {
    }
    virtual ~CalculatorServiceRequestHandler() {}
  public:
    virtual void HandleRequest(::naeem::hottentot::runtime::Request &   /* Request object */, ::naeem::hottentot::runtime::Response &  /* Response object */);
  };
} // END OF NAMESPACE service
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif