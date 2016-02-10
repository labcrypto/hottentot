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

#include "templates/templates.h"

#include "../ds/hot.h"
#include "../ds/service.h"
#include "../ds/method.h"
#include "../ds/module.h"
#include "../ds/argument.h"
#include "../ds/struct.h"
#include "../ds/declaration.h"
#include "../ds/enum.h"

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
          std::string abstractServiceHeaderTemplate((char *)__cc_templates_abstract_service_header_template, __cc_templates_abstract_service_header_template_len);
          std::string enumsTemplate((char *)__cc_templates_enums_template, __cc_templates_enums_template_len);
          std::string proxyBuilderCCTemplate((char *)__cc_templates_proxy_builder_cc_template, __cc_templates_proxy_builder_cc_template_len);
          std::string proxyBuilderHeaderTemplate((char *)__cc_templates_proxy_builder_header_template, __cc_templates_proxy_builder_header_template_len);
          std::string proxyCCTemplate((char *)__cc_templates_proxy_cc_template, __cc_templates_proxy_cc_template_len);
          std::string proxyCCMethodTemplate((char *)__cc_templates_proxy_cc__method_template, __cc_templates_proxy_cc__method_template_len);
          std::string proxyCCMethodArgumentSerializationTemplate((char *)__cc_templates_proxy_cc__method_argument_serialization_template, __cc_templates_proxy_cc__method_argument_serialization_template_len);
          std::string proxyCCMethodResponseDeserialization((char *)__cc_templates_proxy_cc__method_response_deserialization_template, __cc_templates_proxy_cc__method_response_deserialization_template_len);
          std::string proxyHeaderTemplate((char *)__cc_templates_proxy_header_template, __cc_templates_proxy_header_template_len);
          std::string requestHandlerCCTemplate((char *)__cc_templates_request_handler_cc_template, __cc_templates_request_handler_cc_template_len);
          std::string requestHandlerCCMethodIfClauseTemplate((char *)__cc_templates_request_handler_cc__method_if_clause_template, __cc_templates_request_handler_cc__method_if_clause_template_len);
          std::string requestHandlerHeaderTemplate((char *)__cc_templates_request_handler_header_template, __cc_templates_request_handler_header_template_len);
          std::string interfaceTemplate((char *)__cc_templates_interface_template, __cc_templates_interface_template_len);
          std::string serviceInterfaceTemplate((char *)__cc_templates_service_interface_template, __cc_templates_service_interface_template_len);
          std::string structCCTemplate((char *)__cc_templates_struct_cc_template, __cc_templates_struct_cc_template_len);
          std::string structHeaderTemplate((char *)__cc_templates_struct_header_template, __cc_templates_struct_header_template_len);
          std::string structHeaderGetterAndSetterTemplate((char *)__cc_templates_struct_header__getter_and_setter_template, __cc_templates_struct_header__getter_and_setter_template_len);
          std::map<std::string, std::string> templates;
          templates.insert(std::pair<std::string, std::string>("abstract_service_header", abstractServiceHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("enums", enumsTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_builder_cc", proxyBuilderCCTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_builder_header", proxyBuilderHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc", proxyCCTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc__method", proxyCCMethodTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc__method_argument_serialization", proxyCCMethodArgumentSerializationTemplate));
          templates.insert(std::pair<std::string, std::string>("proxy_cc__method_response_deserialization", proxyCCMethodResponseDeserialization));
          templates.insert(std::pair<std::string, std::string>("proxy_header", proxyHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("request_handler_cc", requestHandlerCCTemplate));          
          templates.insert(std::pair<std::string, std::string>("request_handler_cc__method_if_clause", requestHandlerCCMethodIfClauseTemplate));
          templates.insert(std::pair<std::string, std::string>("request_handler_header", requestHandlerHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("interface", interfaceTemplate));
          templates.insert(std::pair<std::string, std::string>("service_interface", serviceInterfaceTemplate));
          templates.insert(std::pair<std::string, std::string>("struct_cc", structCCTemplate));
          templates.insert(std::pair<std::string, std::string>("struct_header", structHeaderTemplate));
          templates.insert(std::pair<std::string, std::string>("struct_header__getter_and_setter", structHeaderGetterAndSetterTemplate));
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
            Runtime::enums_.clear();
            Runtime::enums_.insert(Runtime::enums_.end(),
                                   hot->modules_[moduleCounter]->enums_.begin(), 
                                   hot->modules_[moduleCounter]->enums_.end());
            GenerateEnums(hot->modules_,
                          generationConfig,
                          templates);
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
              GenerateInterface(hot->modules_[moduleCounter]->services_[serviceCounter],
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
        }
      }
    }
  }
}