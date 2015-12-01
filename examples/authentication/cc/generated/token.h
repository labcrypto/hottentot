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
 
#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__TOKEN_H_

#include <string>

#include <naeem/hottentot/runtime/serializable.h>


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        class Token : public ::naeem::hottentot::serialization::Serializable {
        public:
          Token() {}
          ~Token() {}
          inline std::string GetValue() const {
            return value_;
          }
          inline void SetValue(std::string value) {
            value_ = value;
          }
          virtual unsigned char * Serialize(uint32_t *   /* Pointer to length */);
          virtual void Deserialize(unsigned char *       /* Data */,
                                   uint32_t              /* Data length */);
        private:
          std::string value_;
        };
      }
    }
  }
}

#endif
