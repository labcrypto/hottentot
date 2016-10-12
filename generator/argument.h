/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__ARGUMENT_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__ARGUMENT_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

#include <stdio.h>
#ifdef __WIN32__
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  class JavaGenerator;
};
namespace cc {
  class CCGenerator;
};
  class Argument {
    friend class ::org::labcrypto::hottentot::generator::cc::CCGenerator;
    friend class ::org::labcrypto::hottentot::generator::java::JavaGenerator;
  public:
    Argument(std::string type = "", 
             std::string variable = "")
      : type_(type),
        variable_(variable) {
    }
    virtual ~Argument() {}
  public:
    inline std::string GetType() const {
      return type_;
    }
    inline void SetType(std::string type) {
      type_ = type;
    }
    inline std::string GetVariable() const {
      return variable_;
    }
    inline void SetVariable(std::string variable) {
      variable_ = variable;
    }
    inline virtual void Display() {
      std::cout << variable_ << ": " << type_;
    }
  protected:
    std::string type_;
    std::string variable_;
  };
}
}
}
}

#endif