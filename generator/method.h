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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__METHOD_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__METHOD_H_

#include <vector>
#include <iostream>

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

#include "argument.h"


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
  class Argument;
  class Service;
  class Method {
    friend class Hot;
    friend class ::org::labcrypto::hottentot::generator::cc::CCGenerator;
    friend class ::org::labcrypto::hottentot::generator::java::JavaGenerator;
  public:
    Method(Service *service) 
      : service_(service) {
    }
    virtual ~Method() {}
  public:
    inline void AddArgument(Argument *argument) {
      arguments_.push_back(argument);
    }
    inline std::vector<Argument*> GetArguments() {
      return arguments_;
    }
    inline std::string GetReturnType() const {
      return returnType_;
    }
    inline void SetReturnType(std::string returnType) {
      returnType_ = returnType;
    }
    inline std::string GetName() const {
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
      std::cout << "): " << returnType_ << " => '" << GetFQName() << "', Hash: '" << GetHash() << "'";
    }
    virtual std::string GetFQName() const;
    virtual uint32_t GetHash() const;
  private:
    std::string returnType_;
    std::string name_;
    std::vector<Argument*> arguments_;
    Service *service_;
  };
}
}
}
}

#endif