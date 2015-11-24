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

#include <sstream>

#include "method.h"
#include "service.h"

#include "../dep/fasthash.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace ds {
        std::string 
        Method::GetFQName() const {
          std::stringstream ss;
          ss << service_->GetFQName() << "." << name_;
          ss << "(";
          std::string del = "";
          for (uint32_t i = 0; i < arguments_.size(); i++) {
            ss << del << ":" << arguments_[i]->GetType();
            del = ",";
          }
          ss << "):";
          ss << returnType_;
          return ss.str();
        }
        uint32_t 
        Method::GetHash() const {
          std::string fqName = GetFQName();
          return fasthash32(fqName.c_str(), fqName.size(), 0);
        }
      }
    }
  }
}