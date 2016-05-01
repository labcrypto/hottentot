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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__COMMON__TYPE_HELPER_H_
#define _NAEEM_HOTTENTOT_GENERATOR__COMMON__TYPE_HELPER_H_

#include <stdexcept>
#include "runtime.h"

namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace common {
        class TypeHelper {
        public:
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

          static inline bool IsListType(std::string type){
            if(type.find("list") != std::string::npos){
              return true;
            }
            return false;
          }

          static inline std::string FetchTypeOfList(std::string type){
            std::string output = ::naeem::hottentot::generator::common::StringHelper::Replace(type , "list<" , "");
            ::naeem::hottentot::generator::common::StringHelper::Replace(output , ">" , "" , 1);
            return output;
          }

          static inline std::string GetSerializableHottentotType(std::string type) {
            if (type == "int8") {
              return "_Int8";
            } else if (type == "int16") {
              return "_Int16";
            } else if (type == "int32") {
              return "_Int32";
            } else if (type == "int64") {
              return "_Int64";
            } else if (type == "uint8") {
              return "_Int8";
            } else if (type == "uint16") {
              return "_Int16";
            } else if (type == "uint32") {
              return "_Int32";
            } else if (type == "uint64") {
              return "_Int64";
            } else if (type == "bool") {
              return "_Boolean";
            } else if (type == "string") {
              return "_String";
            } else if (type == "char") {
              return "_Char";
            } else if (type == "double") {
              return "_Double";
            } else if (type == "data") {
              return "_Data";
            } else {
              std::runtime_error("Type is not supported");  
            }
            return type;
            
          }

          static inline std::string GetJavaClassType(std::string type) {
            if(IsUDT(type)){
                std::runtime_error("type is not PDT");
            }
            if (type == "int8") {
              return "Byte";
            } else if (type == "int16") {
              return "Short";
            } else if (type == "int32") {
              return "Integer";
            } else if (type == "int64") {
              return "Long";
            } else if (type == "uint8") {
              return "Byte";
            } else if (type == "uint16") {
              return "Short";
            } else if (type == "uint32") {
              return "Integer";
            } else if (type == "uint64") {
              return "Long";
            } else if (type == "bool") {
              return "Boolean";
            } else if (type == "string") {
              return "String";
            } else if (type == "char") {
              return "Character";
            } else if (type == "double") {
              return "Double";
            } else {
               std::runtime_error("type is not supported"); 
            }
            return type;
          }


          static inline std::string GetJavaType(std::string type) {
            if(IsUDT(type)){
                std::runtime_error("type is not PDT");
            }
            if (type == "int8") {
              return "byte";
            } else if (type == "int16") {
              return "short";
            } else if (type == "int32") {
              return "int";
            } else if (type == "int64") {
              return "long";
            } else if (type == "uint8") {
              return "byte";
            } else if (type == "uint16") {
              return "short";
            } else if (type == "uint32") {
              return "int";
            } else if (type == "uint64") {
              return "long";
            } else if (type == "bool") {
              return "boolean";
            } else if (type == "string") {
              return "String";
            } else if (type == "char") {
              return "char";
            } else if (type == "data") {
              return "byte[]";
            } else if (type == "date") {
              return "date";
            } else if (type == "double") {
              return "double";
            } else if (type == "void") {
              return "void";
            }else if (type == "void") {
              return "void";
            }else if (IsListType(type)){
              return "List<" + GetJavaClassType(FetchTypeOfList(type)) + ">";
            }
            return type;
          }

          static inline std::string GetPdtWrapperClassName(std::string type) {
            if(IsUDT(type)) {
                std::runtime_error("type is not PDT");
            }
            if (type == "int8") {
              return "_Int8";
            } else if (type == "int16") {
              return "_Int16";
            } else if (type == "int32") {
              return "_Int32";
            } else if (type == "int64") {
              return "_Int32";
            } else if (type == "uint8") {
              return "_Int8";
            } else if (type == "uint16") {
              return "_Int16";
            } else if (type == "uint32") {
              return "_Int32";
            } else if (type == "uint64") {
              return "_Int64";
            } else if (type == "bool") {
              return "_Boolean";
            } else if (type == "string") {
              return "_String";
            } else if (type == "char") {
              return "_Char";
            } else if (type == "data") {
              return "_Data";
            } else if (type == "date") {
              return "_Date";
            } else if (type == "double") {
              return "_Double";
            } 
            return type;
          }
        
          static inline uint32_t GetTypeLength(std::string type){
            if(IsEnum(type)) {
              return 2;
            }else if (type.compare("int8") == 0 ||
              type.compare("uint8") == 0) {
              return 1;
            } else if (type.compare("int16") == 0 ||
             type.compare("uint16") == 0) {
              return 2;
            } else if (type.compare("int32") == 0 ||
             type.compare("uint32") == 0) {
              return 4;
            } else if (type.compare("int64") == 0 ||
             type.compare("uint64") == 0) {
              return 8;
            } else if (type.compare("bool") == 0) {
              return 1;
            }
            return -1;
          }

          static inline bool IsVoid(std::string type) {
            return ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(type) == "void";
          }
        
          static inline bool IsEnum(std::string type) {
            for (uint32_t i = 0; i < Runtime::enums_.size(); i++) {
              if (Runtime::enums_[i]->GetName() == type) {
                return true;
              }
            }
            return false;
          }
          
        };
      }
    }
  }
}

#endif