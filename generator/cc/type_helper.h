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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__CC__TYPE_HELPER_H_
#define _NAEEM_HOTTENTOT_GENERATOR__CC__TYPE_HELPER_H_

#include "../common/string_helper.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace cc {
        class TypeHelper {
        public:
          static inline bool IsVoid(std::string type) {
            return ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(type) == "void";
          }
          static inline bool IsUDT(std::string type) {
            if (type == "int8") {
              return false;
            } else if (type == "int16") {
              return false;
            } else if (type == "int32") {
              return false;
            } else if (type == "int64") {
              return false;
            } else if (type == "uint8") {
              return false;
            } else if (type == "uint16") {
              return false;
            } else if (type == "uint32") {
              return false;
            } else if (type == "uint64") {
              return false;
            } else if (type == "bool") {
              return false;
            } else if (type == "string") {
              return false;
            } else if (type == "char") {
              return false;
            } else if (type == "data") {
              return false;
            } else if (type == "date") {
              return false;
            } else if (type == "double") {
              return false;
            } else if (type == "void") {
              return false;
            }
            return true;
          }
          static inline std::string GetCCType(std::string type) {
            if (type == "int8") {
              return "int8_t";
            } else if (type == "int16") {
              return "int16_t";
            } else if (type == "int32") {
              return "int32_t";
            } else if (type == "int64") {
              return "int64_t";
            } else if (type == "uint8") {
              return "uint8_t";
            } else if (type == "uint16") {
              return "uint16_t";
            } else if (type == "uint32") {
              return "uint32_t";
            } else if (type == "uint64") {
              return "uint64_t";
            } else if (type == "bool") {
              return "bool";
            } else if (type == "string") {
              return "std::string";
            } else if (type == "char") {
              return "char";
            } else if (type == "data") {
              return "unsigned char *";
            } else if (type == "date") {
              return "uint64_t";
            } else if (type == "double") {
              return "double";
            } else if (type == "void") {
              return "void";
            }
            return type;
          }
        };
      }
    }
  }
}

#endif