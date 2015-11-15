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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__DS__SET_DECLARATION_H_
#define _NAEEM_HOTTENTOT_GENERATOR__DS__SET_DECLARATION_H_

#include "declaration.h"
#include "../string_helper.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace ds {
        class SetDeclaration : public Declaration {
        public:
          SetDeclaration(std::string type = "", 
                         std::string variable = "",
                         std::string ordString = "")
            : Declaration("", variable, ordString) {
              setType_ = type;
          }
          virtual ~SetDeclaration() {}
        public:
          inline virtual DeclarationType GetDeclarationType() const {
            return Set;
          }
          inline virtual std::string GetSetType() const {
            return setType_;
          }
          inline virtual void SetSetType(std::string setType) {
            setType_ = setType;
          }
          inline virtual void Display() {
            std::cout << variable_ << ": SET<" << setType_ << "> with ORD(" << ord_ << ")";
          }
        protected:
          std::string setType_;
        };
      }
    }
  }
}

#endif