/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 10-02-2016 03:06:23
 * Name: token.h
 * Description:
 *   This file contains definition of Token class.
 ***************************************************************/

#ifndef _EXAMPLE_GENERATED_ABC_XYZ__TOKEN_H_
#define _EXAMPLE_GENERATED_ABC_XYZ__TOKEN_H_

#include <string>

#include <naeem/hottentot/runtime/types/primitives.h>
#include <naeem/hottentot/runtime/serializable.h>


namespace example {
namespace generated {
namespace abc {
namespace xyz {
  class Token : public ::naeem::hottentot::runtime::Serializable {
  public:
    Token() {}
    Token(const Token &);
    Token(Token *);
    virtual ~Token() {}
  public:
    inline ::naeem::hottentot::runtime::types::Utf8String GetValue() const {
      return value_;
    }
    inline void SetValue(::naeem::hottentot::runtime::types::Utf8String value) {
      value_ = value;
    }
    inline ::naeem::hottentot::runtime::types::Int16 GetId() const {
      return id_;
    }
    inline void SetId(::naeem::hottentot::runtime::types::Int16 id) {
      id_ = id;
    }
  public:
    virtual unsigned char * Serialize(uint32_t * /* Pointer to length */);
    virtual void Deserialize(unsigned char * /* Data */, uint32_t /* Data length */);
  private:
    ::naeem::hottentot::runtime::types::Utf8String value_;
    ::naeem::hottentot::runtime::types::Int16 id_;
  };
} // END OF NAMESPACE xyz
} // END OF NAMESPACE abc
} // END OF NAMESPACE generated
} // END OF NAMESPACE example

#endif