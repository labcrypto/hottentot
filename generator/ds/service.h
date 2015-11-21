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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__DS__SERVICE_H_
#define _NAEEM_HOTTENTOT_GENERATOR__DS__SERVICE_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
          class JavaGenerator;
      };

      namespace ds {
        class Method;
        class Service {
        friend class Hot;
        friend class ::naeem::hottentot::generator::java::JavaGenerator;
        public:
          enum ServiceType {
            Stateless,
            Stateful
          };
        public:
          Service(std::string serviceTypeString = "stateless",
                  std::string name = "") 
            : name_(name) {
            SetServiceType(serviceTypeString);
          }
          virtual ~Service() {}
        public:
          inline virtual void AddMethod(Method *method) {
            methods_.push_back(method);
          }
          
          inline virtual void SetServiceType(ServiceType serviceType) {
            serviceType_ = serviceType;
          }
          inline virtual ServiceType GetServiceType() {
            return serviceType_;
          }
          inline virtual void SetServiceType(std::string serviceTypeString) {
            if (serviceTypeString == "stateless") {
              serviceType_ = Stateless;
            } else if (serviceTypeString == "stateful") {
              serviceType_ = Stateful;
            } else {
              std::cout << "SEMANTIC ERROR: Wrong type for service. You should either use 'stateless' or 'stateful'." << std::endl;
              exit(1);
            }
          }
          inline virtual std::string GetName() const {
            return name_;
          }
          inline virtual void SetName(std::string name) {
            name_ = name;
          }
        private:
          ServiceType serviceType_;
          std::string name_;
          std::vector<Method*> methods_;
          uint32_t id_;
        };
      }
    }
  }
}

#endif