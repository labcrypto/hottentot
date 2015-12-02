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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME__TYPES__BYTE_ARRAY_H_
#define _NAEEM_HOTTENTOT_RUNTIME__TYPES__BYTE_ARRAY_H_

#include <iostream>
#include <stdexcept>
#include <stdint.h>

#include "../serializable.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace types {
        class ByteArray : public ::naeem::hottentot::runtime::Serializable {
        public:
          ByteArray()
            : data_(0),
              length_(0) {
          }
          ByteArray(unsigned char *data,
                    uint32_t length)
            : data_(data),
              length_(length) {
          }
          virtual ~ByteArray() {}
        public:
          inline void SetValue(unsigned char *data, 
                               uint32_t length) {
            data_ = data;
            length_ = length;
          }
          inline unsigned char* GetValue() const {
            return data_;
          }
          inline uint32_t GetLength() const {
            return length_;
          }
        public:
          inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
            *length_ptr = length_;
            unsigned char *data = 
              new unsigned char[length_ * sizeof(unsigned char)];
            for (uint32_t i = 0; i < length_; i++) {
              data[i] = data_[i];
            }
            return data;
          }
          inline virtual void Deserialize(unsigned char *data,
                                          uint32_t length) {
            data_ = data;
            length_ = length;
          }
        private:
          unsigned char *data_;
          uint32_t length_;
        };
      }
    }
  }
}

#endif