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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME__TYPES__BOOLEAN_H_
#define _NAEEM_HOTTENTOT_RUNTIME__TYPES__BOOLEAN_H_

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <stdint.h>

#include "../serializable.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace types {
        class Boolean : public ::naeem::hottentot::runtime::Serializable {
        public:
          Boolean()
            : value_(0) {
          }
          Boolean(bool value)
            : value_(value) {
          }
          virtual ~Boolean() {}
        public:
          inline void SetValue(bool value) {
            value_ = value;
          }
          inline bool GetValue() const {
            return value_;
          }
        public:
          inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
            *length_ptr = 1 * sizeof(unsigned char);
            unsigned char *data = (unsigned char *)malloc(1 * sizeof(unsigned char));
            data[0] = value_ ? 1 : 0;
            return data;
          }
          inline virtual void Deserialize(unsigned char *data,
                                          uint32_t length) {
            if (length != 1) {
              throw std::runtime_error("Length is not correct for deserialization.");
            }
            value_ = data[0] != 0;
          }
        private:
          bool value_;
        };
      }
    }
  }
}

#endif