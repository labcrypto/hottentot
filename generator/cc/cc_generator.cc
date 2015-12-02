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
#include "type_helper.h"

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
          std::string abstractServiceHeaderTemplate;
          std::string proxyBuilderCCTemplate;
          std::string proxyBuilderHeaderTemplate;
          std::string proxyCCTemplate;
          std::string proxyCCMethodTemplate;
          std::string proxyCCMethodArgumentSerializationTemplate;
          std::string proxyCCMethodResponseDeserialization;
          std::string proxyHeaderTemplate;
          std::string requestHandlerCCTemplate;
          std::string requestHandlerCCMethodIfClauseTemplate;
          std::string requestHandlerHeaderTemplate;
          std::string serviceInterfaceTemplate;
          std::string structCCTemplate;
          std::string structHeaderTemplate;
          std::string structHeaderGetterAndSetterTemplate;
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/abstract_service_header.template", abstractServiceHeaderTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_builder_cc.template", proxyBuilderCCTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_builder_header.template", proxyBuilderHeaderTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_cc.template", proxyCCTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_cc__method.template", proxyCCMethodTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_cc__method_argument_serialization.template", proxyCCMethodArgumentSerializationTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_cc__method_response_deserialization.template", proxyCCMethodResponseDeserialization);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/proxy_header.template", proxyHeaderTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/request_handler_cc.template", requestHandlerCCTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/request_handler_cc__method_if_clause.template", requestHandlerCCMethodIfClauseTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/request_handler_header.template", requestHandlerHeaderTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/service_interface.template", serviceInterfaceTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/struct_cc.template", structCCTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/struct_header.template", structHeaderTemplate);
          ::naeem::hottentot::generator::common::Os::ReadFile("cc/templates/struct_header__getter_and_setter.template", structHeaderGetterAndSetterTemplate);
          std::map<std::string, std::string> templates;
          templates.insert(std::pair<std::string, std::string>("abstract_service_header",abstractServiceHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_builder_cc",proxyBuilderCCTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_builder_header",proxyBuilderHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc",proxyCCTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc__method",proxyCCMethodTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc__method_argument_serialization",proxyCCMethodArgumentSerializationTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc__method_response_deserialization",proxyCCMethodResponseDeserialization));
          templates.insert(std::pair<std::string, std::string>("proxy_header",proxyHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("request_handler_cc",requestHandlerCCTemplate));          
          templates.insert(std::pair<std::string, std::string>("request_handler_cc__method_if_clause",requestHandlerCCMethodIfClauseTemplate));
          templates.insert(std::pair<std::string, std::string>("request_handler_header",requestHandlerHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("service_interface",serviceInterfaceTemplate));
          templates.insert(std::pair<std::string, std::string>("struct_cc",structCCTemplate));
          templates.insert(std::pair<std::string, std::string>("struct_header",structHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("struct_header__getter_and_setter",structHeaderGetterAndSetterTemplate));
          /*
           * Creating needed directories
           */
          ::naeem::hottentot::generator::common::Os::MakeDir(generationConfig.GetOutDir() + "/proxy");
          ::naeem::hottentot::generator::common::Os::MakeDir(generationConfig.GetOutDir() + "/service");
          /*
           * Proceed to generate files
           */
          for (uint32_t moduleCounter = 0; 
               moduleCounter < hot->modules_.size();
               moduleCounter++) {
            for (uint32_t structCounter = 0; 
                 structCounter < hot->modules_[moduleCounter]->structs_.size();
                 structCounter++) {
              GenerateStructHeader(hot->modules_[moduleCounter]->structs_[structCounter],
                                   generationConfig,
                                   templates);
              GenerateStructCC(hot->modules_[moduleCounter]->structs_[structCounter],
                               generationConfig,
                               templates);
            }
            for (uint32_t serviceCounter = 0;
                 serviceCounter < hot->modules_[moduleCounter]->services_.size();
                 serviceCounter++) {
              GenerateAbstractServiceHeader(hot->modules_[moduleCounter]->services_[serviceCounter],
                                            generationConfig,
                                            templates);
              GenerateServiceInterface(hot->modules_[moduleCounter]->services_[serviceCounter],
                                       generationConfig,
                                       templates);
              GenerateProxyHeader(hot->modules_[moduleCounter]->services_[serviceCounter],
                                  generationConfig,
                                  templates);
              GenerateProxyCC(hot->modules_[moduleCounter]->services_[serviceCounter],
                              generationConfig,
                              templates);
              GenerateProxyBuilderHeader(hot->modules_[moduleCounter]->services_[serviceCounter],
                                         generationConfig,
                                         templates);
              GenerateProxyBuilderCC(hot->modules_[moduleCounter]->services_[serviceCounter],
                                     generationConfig,
                                     templates);
              GenerateRequestHandlerHeader(hot->modules_[moduleCounter]->services_[serviceCounter],
                                           generationConfig,
                                           templates);
              GenerateRequestHandlerCC(hot->modules_[moduleCounter]->services_[serviceCounter],
                                       generationConfig,
                                       templates);
            }
          }
          // std::cout << "C++ Generation done." << std::endl;
        }
      }
    }
  }
}