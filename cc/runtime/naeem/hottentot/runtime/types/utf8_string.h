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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME__TYPES__UTF8_STRING_H_
#define _NAEEM_HOTTENTOT_RUNTIME__TYPES__UTF8_STRING_H_

#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <string.h>

#include "../serializable.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace types {
        class Utf8String : public ::naeem::hottentot::runtime::Serializable {
        public:
          Utf8String(const char *data = 0)
            : data_(0),
              chars_(0),
              length_(0) {
            if (data) {
              FromByteArray(data);
            }
          }
          virtual ~Utf8String() {
            uint32_t byteLength = strlen(data_);
            for (uint32_t i = 0; i < byteLength; i++) {
              std::cout << "BYE: " << data_[i] << std::endl;
            }
            if (data_) {
              delete [] data_;
            }
            if (chars_) {
              delete [] chars_;
            }
          }
        public:
          uint32_t Length() const {
           return length_;
          }
          uint16_t CharAt(uint32_t index) const {
            return chars_[index];
          }
        public:
          inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
            uint32_t byteLength = strlen(data_);
            unsigned char *data = new unsigned char[byteLength + 1];
            for (uint32_t i = 0; i < byteLength; i++) {
              data[i] = data_[i];
            }
            data[byteLength] = 0;
            *length_ptr = byteLength + 1;
            return data;
          }
          inline virtual void Deserialize(unsigned char *data,
                                          uint32_t length) {
            FromByteArray((const char *)data);
          }
        protected:
          inline void FromByteArray(const char *data) {
            uint32_t byteLength = strlen(data);
            std::cout << "BL: " << byteLength << std::endl;
            if (data_) {
              delete [] data_;
            }
            data_ = new char[byteLength + 1];
            for (uint32_t i = 0; i < byteLength; i++) {
              data_[i] = data[i];
            }
            data_[byteLength] = 0;
            length_ = 0;
            for (uint32_t i = 0; i < byteLength; i++) {
              std::cout << "CHAR: " << data_[i] << std::endl;
              if ((data_[i] & 0x80) == 0x00) {
                length_++;
              } else {
                if ((data_[i] & 0x40) == 0x40 && (data_[i] & 0x20) == 0x00) {
                  length_++;
                }
              }
            }
            std::cout << "LLLL: " << length_ << std::endl;
            uint32_t c = 0;
            chars_ = new uint16_t[length_ + 1];
            for (uint32_t i = 0; i < byteLength; i++) {
              if ((data_[i] & 0x80) == 0x00) {
                chars_[c++] = data_[i];
              } else {
                if ((data_[i] & 0x40) == 0x40 && (data_[i] & 0x20) == 0x00) {
                  uint16_t left = data_[i] & 0x1f;
                  uint16_t right = data_[i + 1] & 0x3f;
                  uint16_t result = right | (left << 6);
                  chars_[c++] = result;
                }
              }
            }
            chars_[c] = 0;
            std::cout << "LLLL ccc: " << c << std::endl;
          }
        private:
          char *data_;
          uint16_t *chars_;
          uint32_t length_;
        };
      }
    }
  }
}

#endif