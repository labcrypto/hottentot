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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__ENUM_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__ENUM_H_

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
  class Enum {
    friend class Hot;
    friend class ::naeem::hottentot::generator::cc::CCGenerator;
    friend class ::naeem::hottentot::generator::java::JavaGenerator;
  public:
    public:
    Enum(Module *module) 
      :  module_(module) {
    }
    virtual ~Enum() {}
  public:
    inline virtual void AddItem(std::string name, uint16_t value) {
      items_[name] = value;
      revItems_[value] = name;
    }
    inline virtual std::string GetName() const {
      return name_;
    }
    inline virtual void SetName(std::string name) {
      name_ = name;
    }
    inline virtual std::string GetItemName(uint16_t itemValue) {
      return revItems_[itemValue];
    }
    inline virtual uint16_t GetItemValue(std::string itemName) {
      return items_[itemName];
    }
  private:
    std::string name_;
    std::map<std::string, uint16_t> items_;
    std::map<uint16_t, std::string> revItems_;
    Module *module_;
  };
}
}
}
}

#endif