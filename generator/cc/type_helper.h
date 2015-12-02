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
              return "::naeem::hottentot::runtime::types::Int8";
            } else if (type == "int16") {
              return "::naeem::hottentot::runtime::types::Int16";
            } else if (type == "int32") {
              return "::naeem::hottentot::runtime::types::Int32";
            } else if (type == "int64") {
              return "::naeem::hottentot::runtime::types::Int64";
            } else if (type == "uint8") {
              return "::naeem::hottentot::runtime::types::UInt8";
            } else if (type == "uint16") {
              return "::naeem::hottentot::runtime::types::UInt16";
            } else if (type == "uint32") {
              return "::naeem::hottentot::runtime::types::UInt32";
            } else if (type == "uint64") {
              return "::naeem::hottentot::runtime::types::UInt64";
            } else if (type == "bool") {
              return "::naeem::hottentot::runtime::types::Boolean";
            } else if (type == "string") {
              return "::naeem::hottentot::runtime::types::Utf8String";
            } else if (type == "char") {
              return "::naeem::hottentot::runtime::types::Char";
            } else if (type == "data") {
              return "::naeem::hottentot::runtime::types::ByteArray";
            } else if (type == "date") {
              return "::naeem::hottentot::runtime::types::Date";
            } else if (type == "time") {
              return "::naeem::hottentot::runtime::types::Time";
            } else if (type == "datetime") {
              return "::naeem::hottentot::runtime::types::DateTime";
            } else if (type == "double") {
              return "::naeem::hottentot::runtime::types::Double";
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