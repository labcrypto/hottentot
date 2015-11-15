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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__DS__METHOD_H_
#define _NAEEM_HOTTENTOT_GENERATOR__DS__METHOD_H_

#include <vector>

#include "argument.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace ds {
        class Argument;
        class Method {
        friend class Hot;
        public:
          Method() {}
          virtual ~Method() {}
        public:
          inline virtual void AddArgument(Argument *argument) {
            arguments_.push_back(argument);
          }
          inline virtual std::string GetReturnType() const {
            return returnType_;
          }
          inline virtual void SetReturnType(std::string returnType) {
            returnType_ = returnType;
          }
          inline virtual std::string GetName() const {
            return name_;
          }
          inline void SetName(std::string name) {
            name_ = name;
          }
          inline virtual void Display() {
            std::cout << name_ <<  "(";
            std::string del = "";
            for (uint32_t i = 0; i < arguments_.size(); i++) {
              std::cout << del;
              arguments_[i]->Display();
              del = ",";
            }
            std::cout << "): " << returnType_;
          }
        private:
          std::string returnType_;
          std::string name_;
          std::vector<Argument*> arguments_;
        };
      }
    }
  }
}

#endif