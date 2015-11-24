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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__DS__HOT_H_
#define _NAEEM_HOTTENTOT_GENERATOR__DS__HOT_H_

#include <vector>
#include <iostream>
#include <stdint.h>

#include "module.h"
#include "struct.h"
#include "service.h"
#include "declaration.h"
#include "method.h"
#include "argument.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java{
          class JavaGenerator;
      };

      namespace ds {
        class Module;
        class Hot {
        
        friend class ::naeem::hottentot::generator::java::JavaGenerator;
        public:
          Hot() {}
          virtual ~Hot() {}
        public:
          inline void AddModule(Module *module) {
            modules_.push_back(module);
          }
         
          inline virtual void Display() {
            std::cout << "HOT {\n";
            for (uint32_t i = 0; i < modules_.size(); i++) {
              std::cout << "   MODULE " << modules_[i]->package_ << " {\n";
              for (uint32_t j = 0; j < modules_[i]->structs_.size(); j++) {
                std::cout << "      STRUCT " <<  modules_[i]->structs_[j]->GetName() << " {\n";
                for (std::map<uint32_t, Declaration*>::iterator it = modules_[i]->structs_[j]->declarations_.begin();
                     it != modules_[i]->structs_[j]->declarations_.end();
                     ++it) {
                  std::cout << "         ";
                  it->second->Display();
                  std::cout << std::endl;
                }
                std::cout << "      }\n";
              }
              for (uint32_t j = 0; j < modules_[i]->services_.size(); j++) {
                std::cout << "      ";
                std::cout << (modules_[i]->services_[j]->GetServiceType() == ::naeem::hottentot::generator::ds::Service::Stateless ? "STATELESS" : "STATEFUL");
                std::cout << " SERVICE " <<  modules_[i]->services_[j]->GetName() << std::endl;
                std::cout << "      FQName: '" << modules_[i]->services_[j]->GetFQName() << "'" << std::endl;
                std::cout << "      Hash: '" << modules_[i]->services_[j]->GetHash() << "'";
                std::cout << " {\n";
                for (uint32_t k = 0; k < modules_[i]->services_[j]->methods_.size(); k++) {
                  std::cout << "         ";
                  modules_[i]->services_[j]->methods_[k]->Display();
                  std::cout << std::endl;
                }
                std::cout << "      }\n";
              }
              std::cout << "   }\n";
            }
            std::cout << "}\n";
          }
        private:
          std::vector<Module*> modules_;
        };
      }
    }
  }
}

#endif