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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__STRUCT_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__STRUCT_H_

#include <map>

 #include "declaration.h"


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
  class Module;
  class Struct {
    friend class Hot;
    friend class ::naeem::hottentot::generator::cc::CCGenerator;
    friend class ::naeem::hottentot::generator::java::JavaGenerator;
  public:
    public:
    Struct(Module *module) 
      :  module_(module) {
    }
    virtual ~Struct() {}
  public:
    inline virtual void AddDeclaration(Declaration *declaration) {
      declarations_.insert(std::pair<uint32_t, Declaration*>(declaration->GetOrd(), declaration));
    }
    inline virtual std::string GetName() const {
      return name_;
    }
    inline virtual void SetName(std::string name) {
      name_ = name;
    }
  private:
    std::string name_;
    std::map<uint32_t, Declaration*> declarations_;
    Module *module_;
  };
}
}
}
}

#endif