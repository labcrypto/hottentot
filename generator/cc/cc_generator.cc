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

#include <iostream>
#include <fstream>

#include "cc_generator.h"

#include "../ds/hot.h"
#include "../ds/service.h"
#include "../ds/method.h"
 #include "../ds/module.h"
#include "../ds/argument.h"
#include "../ds/struct.h"
#include "../ds/declaration.h"

#include "../common/os.h"
#include "../common/string_helper.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace cc {
        void
        CCGenerator::Generate(::naeem::hottentot::generator::ds::Hot *hot,
                              ::naeem::hottentot::generator::GenerationConfig &generationConfig) {
          /*
           * Reading all needed templates and stroing them in a map
           */
          std::string proxyCCTemplate;
          std::string proxyCCMethodTemplate;
          std::string proxyCCMethodArgumentSerializationTemplate;
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_cc.template", proxyCCTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_method.template", proxyCCMethodTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_method_argument_serialization.template", proxyCCMethodArgumentSerializationTemplate);
          std::map<std::string, std::string> templates;
          templates.insert(std::pair<std::string, std::string>("proxy_cc",proxyCCTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc_method",proxyCCMethodTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc_method_argument_serialization",proxyCCMethodArgumentSerializationTemplate));
          /*
           * Making needed directories
           */
          ::naeem::hottentot::generator::common::Os::MakeDir(generationConfig.GetOutDir() + "/proxy");
          ::naeem::hottentot::generator::common::Os::MakeDir(generationConfig.GetOutDir() + "/service");
          /*
           * Proceed to generate files
           */
          for (uint32_t moduleCounter = 0; 
               moduleCounter < hot->modules_.size(); 
               moduleCounter++) {
            for (uint32_t serviceCounter = 0; 
                 serviceCounter < hot->modules_[moduleCounter]->services_.size();
                 serviceCounter++) {
              GenerateProxy(hot->modules_[moduleCounter]->services_[serviceCounter],
                            generationConfig,
                            templates);
              GenerateProxyBuilder(hot->modules_[moduleCounter]->services_[serviceCounter],
                                   generationConfig,
                                   templates);
            }
          }
          std::cout << "C++ Generation done." << std::endl;
        }
        void
        CCGenerator::GenerateProxy(::naeem::hottentot::generator::ds::Service *service,
                                   ::naeem::hottentot::generator::GenerationConfig &generationConfig,
                                   std::map<std::string, std::string> &templates) {
          std::string serviceNameCamelCaseFirstCapital = 
          ::naeem::hottentot::generator::common::StringHelper::MakeCamelCaseFirstCapital(
            service->GetName()) + "Service";
          std::string serviceSnakeCase = 
            ::naeem::hottentot::generator::common::StringHelper::MakeSnakeCaseFromCamelCase(
              serviceNameCamelCaseFirstCapital);
          std::string serviceProxyHeaderFilePath = generationConfig.GetOutDir() + "/proxy/" + serviceSnakeCase + "_proxy.h";
          std::string serviceProxyCCFilePath = generationConfig.GetOutDir() + "/proxy/" + serviceSnakeCase + "_proxy.cc";
          std::cout << serviceNameCamelCaseFirstCapital << std::endl;
          std::cout << serviceSnakeCase << std::endl;
          std::fstream f;
          f.open(serviceProxyHeaderFilePath.c_str(), std::fstream::out | std::fstream::binary);
          f.close();
          std::fstream f2;
          f2.open(serviceProxyCCFilePath.c_str(), std::fstream::out | std::fstream::binary);
          f2.close();
        }
        void
        CCGenerator::GenerateProxyBuilder(::naeem::hottentot::generator::ds::Service *service,
                                          ::naeem::hottentot::generator::GenerationConfig &generationConfig,
                                          std::map<std::string, std::string> &templates) {
          std::string serviceNameCamelCaseFirstCapital = 
          ::naeem::hottentot::generator::common::StringHelper::MakeCamelCaseFirstCapital(
            service->GetName()) + "Service";
          std::string serviceSnakeCase = 
            ::naeem::hottentot::generator::common::StringHelper::MakeSnakeCaseFromCamelCase(
              serviceNameCamelCaseFirstCapital);
          std::string serviceProxyBuilderHeaderFilePath = generationConfig.GetOutDir() + "/proxy/" + serviceSnakeCase + "_proxy_builder.h";
          std::string serviceProxyBuilderCCFilePath = generationConfig.GetOutDir() + "/proxy/" + serviceSnakeCase + "_proxy_builder.cc";
          std::cout << serviceNameCamelCaseFirstCapital << std::endl;
          std::cout << serviceSnakeCase << std::endl;
          std::fstream f;
          f.open(serviceProxyBuilderHeaderFilePath.c_str(), std::fstream::out | std::fstream::binary);
          f.close();
          std::fstream f2;
          f2.open(serviceProxyBuilderCCFilePath.c_str(), std::fstream::out | std::fstream::binary);
          f2.close();
        }
      }
    }
  }
}