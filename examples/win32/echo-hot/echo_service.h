/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 01-02-2016 01:45:06
 * Name: echo_service.h
 * Description:
 *   This file contains definition of service interface.
 ***************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_WIN32_ECHO__PROXY__ECHO_SERVICE_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_WIN32_ECHO__PROXY__ECHO_SERVICE_H_

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

#include <naeem/hottentot/runtime/types/primitives.h>

#include "echo_request.h"
#include "echo_response.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace win32 {
namespace echo {
  class EchoService {
  public:
    virtual void DoEcho(::ir::ntnaeem::hottentot::examples::win32::echo::EchoRequest &req, ::ir::ntnaeem::hottentot::examples::win32::echo::EchoResponse &out) = 0;
  };
} // END OF NAMESPACE echo
} // END OF NAMESPACE win32
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif