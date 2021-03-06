/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 05:18:41
 * Name: token.h
 * Description:
 *   This file contains definition of Token class.
 ***************************************************************/

#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_

#include <string>

#include <org/labcrypto/hottentot/primitives.h>


#include "enums.h"


namespace naeem {
namespace hottentot {
namespace examples {
namespace auth {
  class Token : public ::org::labcrypto::hottentot::Serializable {
  public:
    Token() {
    }
    Token(const Token &);
    Token(Token *);
    virtual ~Token() {}
  public:
    inline ::org::labcrypto::hottentot::Utf8String GetValue() const {
      return value_;
    }
    inline void SetValue(::org::labcrypto::hottentot::Utf8String value) {
      value_ = value;
    }
  public:
    virtual unsigned char * Serialize(uint32_t * /* Pointer to length */);
    virtual void Deserialize(unsigned char * /* Data */, uint32_t /* Data length */);
  private:
    ::org::labcrypto::hottentot::Utf8String value_;
  };
} // END OF NAMESPACE auth
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE naeem

#endif