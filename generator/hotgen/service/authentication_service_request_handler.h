/***********************************************************************
 * Generated by Hottentot CC Generator
 * Date: 10-02-2016 03:06:23
 * Name: authentication_service_request_handler.h
 * Description:
 *   This file contains definition of service's request handler class.
 ***********************************************************************/

#ifndef _EXAMPLE_GENERATED_ABC_XYZ__SERVICE__AUTHENTICATION_SERVICE_REQUEST_HANDLER_H_
#define _EXAMPLE_GENERATED_ABC_XYZ__SERVICE__AUTHENTICATION_SERVICE_REQUEST_HANDLER_H_

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


namespace example {
namespace generated {
namespace abc {
namespace xyz {
namespace service {
  class AuthenticationServiceRequestHandler : public ::naeem::hottentot::runtime::service::RequestHandler {
  public:
    AuthenticationServiceRequestHandler(::naeem::hottentot::runtime::service::Service *service)
      : ::naeem::hottentot::runtime::service::RequestHandler(service) {
    }
    virtual ~AuthenticationServiceRequestHandler() {}
  public:
    virtual void HandleRequest(::naeem::hottentot::runtime::Request &request,
                                                   ::naeem::hottentot::runtime::Response &response);
  };
} // END OF NAMESPACE service
} // END OF NAMESPACE xyz
} // END OF NAMESPACE abc
} // END OF NAMESPACE generated
} // END OF NAMESPACE example

#endif