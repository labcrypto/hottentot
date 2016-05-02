/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__TYPES__INT32_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__TYPES__INT32_H_

#include <iostream>
#include <stdexcept>

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

#include "serializable.h"


namespace org {
namespace labcrypto {
namespace hottentot {
  class Int32 : public ::naeem::hottentot::runtime::Serializable {
  public:
    Int32()
      : value_(0) {
    }
    Int32(bool value)
      : value_(value ? 1 : 0) {
    }
    Int32(int8_t value)
      : value_((int32_t)value) {
    }
    Int32(int16_t value)
      : value_((int32_t)value) {
    }
    Int32(int32_t value)
      : value_(value) {
    }
    Int32(int64_t value)
      : value_((int32_t)value) {
    }
    Int32(uint8_t value)
      : value_((int32_t)value) {
    }
    Int32(uint16_t value)
      : value_((int32_t)value) {
    }
    Int32(uint32_t value)
      : value_((int32_t)value) {
    }
    Int32(uint64_t value)
      : value_((int32_t)value) {
    }
    virtual ~Int32() {}
  public:
    inline void SetValue(int32_t value) {
      value_ = value;
    }
    inline int32_t GetValue() const {
      return value_;
    }
  public:
    friend std::ostream& operator <<(std::ostream& out, const Int32& obj) {
      out << obj.value_;
      return out;
    }
  public:
    inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
      *length_ptr = 4 * sizeof(unsigned char);
      unsigned char *data = 
        new unsigned char[4 * sizeof(unsigned char)];
      unsigned char *ptr = (unsigned char*)(&value_);
      data[0] = ptr[3];
      data[1] = ptr[2];
      data[2] = ptr[1];
      data[3] = ptr[0];
      return data;
    }
    inline virtual void Deserialize(unsigned char *data,
                                    uint32_t length) {
      if (length != 4) {
        throw std::runtime_error("Int32: Length is not correct for deserialization.");
      }
      unsigned char *ptr = (unsigned char*)(&value_);
      ptr[0] = data[3];
      ptr[1] = data[2];
      ptr[2] = data[1];
      ptr[3] = data[0];
    }
  private:
    int32_t value_;
  };
}
}
}

#endif