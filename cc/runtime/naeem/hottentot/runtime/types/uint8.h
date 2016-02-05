/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME__TYPES__UINT8_H_
#define _NAEEM_HOTTENTOT_RUNTIME__TYPES__UINT8_H_

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

#include "../serializable.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace types {
        class UInt8 : public ::naeem::hottentot::runtime::Serializable {
        public:
          UInt8()
            : value_(0) {
          }
          UInt8(uint8_t value)
            : value_(value) {
          }
          virtual ~UInt8() {}
        public:
          inline void SetValue(uint8_t value) {
            value_ = value;
          }
          inline uint8_t GetValue() const {
            return value_;
          }
        public:
          friend std::ostream& operator <<(std::ostream& out, const UInt8& obj) {
            out << (unsigned int)obj.value_;
            return out;
          }
        public:
          inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
            *length_ptr = 1 * sizeof(unsigned char);
            unsigned char *data = 
              new unsigned char[1 * sizeof(unsigned char)];
            unsigned char *ptr = (unsigned char*)(&value_);
            data[0] = ptr[0];
            return data;
          }
          inline virtual void Deserialize(unsigned char *data,
                                          uint32_t length) {
            if (length != 1) {
              throw std::runtime_error("UInt8: Length is not correct for deserialization.");
            }
            unsigned char *ptr = (unsigned char*)(&value_);
            ptr[0] = data[0];
          }
        private:
          uint8_t value_;
        };
      }
    }
  }
}

#endif