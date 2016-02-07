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
#include <iomanip>
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
        class ByteArray : public ::naeem::hottentot::runtime::Serializable {
        public:
          ByteArray()
            : data_(0),
              length_(0) {
          }
          ByteArray(unsigned char *data,
                    uint32_t length)
            : data_(0),
              length_(0) {
            FromByteArray(data, length);
          }
          ByteArray(const ByteArray &byteArray)
            : data_(0),
              length_(0) {
            FromByteArray(byteArray.data_, byteArray.length_);
          }
          virtual ~ByteArray() {
            if (data_) {
              delete [] data_;
            }
          }
        public:
          inline void SetValue(unsigned char *data, 
                               uint32_t length) {
            FromByteArray(data, length);
          }
          inline unsigned char* GetValue() const {
            return data_;
          }
          inline uint32_t GetLength() const {
            return length_;
          }
        public:
          inline void Fill(unsigned char **bufferPointer,
                           uint32_t *lengthPointer) {
            if (!data_) {
              *bufferPointer = 0;
              *lengthPointer = 0;
              return;
            }
            *lengthPointer = length_;
            *(bufferPointer) = new unsigned char[length_];
            for (uint32_t i = 0; i < length_; i++) {
              *(bufferPointer)[i] = data_[i];
            }
          }
        public:
          inline ByteArray& operator =(const ByteArray &other) {
            FromByteArray(other.data_, other.length_);
            return *this;
          }
          friend std::ostream& operator <<(std::ostream& out, const ByteArray& obj) {
            out << "BYTE ARRAY:" << std::endl;
            bool newLineInserted = false;
            for (uint32_t i = 0; i < obj.length_; i++) {
              newLineInserted = false;
              out << std::uppercase << std::hex << "0x" << 
                std::setw(2) << std::setfill ('0') << (unsigned int)(obj.data_[i]) << " ";
              if ((i + 1) % 8 == 0) {
                out << std::endl;
                newLineInserted = true;
              }
            }
            if (!newLineInserted) {
              out << std::endl;
            }
            out << std::dec;
            return out;
          }
        public:
          inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
            if (length_ptr) {
              *length_ptr = length_;
            }
            unsigned char *data = 
              new unsigned char[length_ * sizeof(unsigned char)];
            for (uint32_t i = 0; i < length_; i++) {
              data[i] = data_[i];
            }
            return data;
          }
          inline virtual void Deserialize(unsigned char *data,
                                          uint32_t length) {
            FromByteArray(data, length);
          }
        private:
          inline void FromByteArray(unsigned char *data,
                                    uint32_t length) {
            if (length == 0) {
              if (data_) {
                delete [] data_;
              }
              data_ = 0;
              length_ = 0;
              return;
            }
            length_ = length;
            if (data_) {
              delete [] data_;
            }
            data_ = new unsigned char[length_];
            for (uint32_t i = 0; i < length_; i++) {
              data_[i] = data[i];
            }
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