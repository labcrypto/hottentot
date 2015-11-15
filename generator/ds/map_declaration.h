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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__DS__MAP_DECLARATION_H_
#define _NAEEM_HOTTENTOT_GENERATOR__DS__MAP_DECLARATION_H_

#include "declaration.h"
#include "../string_helper.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace ds {
        class MapDeclaration : public Declaration {
        public:
          MapDeclaration(std::string keyType = "", 
                         std::string valueType = "",
                         std::string variable = "",
                         std::string idString = "")
            : Declaration("", variable, idString) {
              keyType_ = keyType;
              valueType_ = valueType;
          }
          virtual ~MapDeclaration() {}
        public:
          inline virtual DeclarationType GetDeclarationType() const {
            return Map;
          }
          inline virtual std::string GetKeyType() const {
            return keyType_;
          }
          inline virtual void SetKeyType(std::string keyType) {
            keyType_ = keyType;
          }
          inline virtual void Display() {
            std::cout << variable_ << ": MAP<" << keyType_ << ", " << valueType_ << "> with id(" << id_ << ")";
          }
        protected:
          std::string keyType_;
          std::string valueType_;
        };
      }
    }
  }
}

#endif