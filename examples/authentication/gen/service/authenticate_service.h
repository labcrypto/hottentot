/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 05:18:41
 * Name: authenticate_service.h
 * Description:
 *   This file contains definition of service interface.
 ***************************************************************/

#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__AUTHENTICATE_SERVICE_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__SERVICE__AUTHENTICATE_SERVICE_H_

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

#include "../credential.h"
#include "../user.h"
#include "../token.h"


namespace naeem {
namespace hottentot {
namespace examples {
namespace auth {
namespace service {
  class AuthenticateService {
  public:
     AuthenticateService() {}
     virtual ~AuthenticateService() {}
  public:
    virtual void Authenticate(
      ::naeem::hottentot::examples::auth::Credential &credential, 
      ::naeem::hottentot::examples::auth::Token &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    ) = 0;
    virtual void F(
      ::org::labcrypto::hottentot::Utf8String &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    ) = 0;
    virtual void G(
      ::org::labcrypto::hottentot::Int32 &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    ) = 0;
    virtual void H(
      ::org::labcrypto::hottentot::ByteArray &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    ) = 0;
  };
} // END OF NAMESPACE service
} // END OF NAMESPACE auth
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE naeem

#endif