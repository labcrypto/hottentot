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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__MODULE_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__MODULE_H_

#include <vector>

#include "service.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
        class JavaGenerator;
      };
      namespace cc {
        class CCGenerator;
      };
      namespace ds {
        class Enum;
        class Struct;
        class Service;
        class Module {
          friend class Hot;
          friend class ::naeem::hottentot::generator::cc::CCGenerator;
          friend class ::naeem::hottentot::generator::java::JavaGenerator;
        public:
          Module() {}
          virtual ~Module() {}
        public:
          inline void AddEnum(Enum *enumm) {
            enums_.push_back(enumm);
          }
          inline void AddStruct(Struct *struc) {
            structs_.push_back(struc);
          }
          inline void AddService(Service *service) {
            services_.push_back(service);
          }
          inline void SetPackage(std::string package) {
            package_ = package;
          }
          inline std::string GetPackage() const {
            return package_;
          }
        private:
          std::string package_;
          std::vector<Enum*> enums_;
          std::vector<Struct*> structs_;
          std::vector<Service*> services_;
        };
      }
    }
  }
}

#endif