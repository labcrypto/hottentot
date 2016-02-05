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
#include <string.h>

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
          Utf8String(const Utf8String &utf8String) 
            : data_(0),
              chars_(0),
              length_(0) {
            if (utf8String.data_) {
              FromByteArray(utf8String.data_);
            }
          }
          virtual ~Utf8String() {
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
          std::string ToStdString() {
            return (const char*)Serialize(NULL);
          }
          std::wstring ToStdWString() {
            // TODO
            return std::wstring();
          }
        public:
          inline Utf8String& operator=(const char *str) {
            FromByteArray(str);
            return *this;
          }
          inline Utf8String& operator=(const Utf8String &other) {
            FromByteArray(other.data_);
            return *this;
          }
          friend std::ostream& operator <<(std::ostream& out, const Utf8String& obj) {
              out << obj.data_;
              return out;
          }
        public:
          inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
            if (!data_) {
              unsigned char *data = new unsigned char[1];
              data[0] = 0;
              *length_ptr = 1;
              return data;
            }
            uint32_t byteLength = strlen(data_);
            unsigned char *data = new unsigned char[byteLength + 1];
            for (uint32_t i = 0; i < byteLength; i++) {
              data[i] = data_[i];
            }
            data[byteLength] = 0;
            if (length_ptr) {
              *length_ptr = byteLength + 1;
            }
            return data;
          }
          inline virtual void Deserialize(unsigned char *data,
                                          uint32_t length) {
            if (length == 0) {
              FromByteArray(0);
              return;
            }
            FromByteArray((const char *)data);
          }
        protected:
          inline void FromByteArray(const char *data) {
            if (!data) {
              if (data_) {
                delete [] data_;
              }
              data_ = 0;
              length_ = 0;
              return;
            }
            uint32_t byteLength = strlen(data);
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
              if ((data_[i] & 0x80) == 0x00) {
                length_++;
              } else {
                if ((data_[i] & 0x40) == 0x40 && (data_[i] & 0x20) == 0x00) {
                  length_++;
                }
              }
            }
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