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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__DS__LIST_DECLARATION_H_
#define _NAEEM_HOTTENTOT_GENERATOR__DS__LIST_DECLARATION_H_

#include "declaration.h"
#include "../string_helper.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace ds {
        class ListDeclaration : public Declaration {
        public:
          ListDeclaration(std::string type = "", 
                          std::string variable = "",
                          uint32_t id = 0)
            : Declaration(::naeem::hottentot::generator::StringHelper::trim(type), variable, id) {
              listType_ = type_.substr(5, type_.size() - 6);
          }
          virtual ~ListDeclaration() {}
        public:
          inline virtual std::string GetListType() const {
            return listType_;
          }
          inline virtual void SetListType(std::string listType) {
            listType_ = listType;
          }
        protected:
          std::string listType_;
        };
      }
    }
  }
}

#endif