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

#include "../common/os.h"
#include "../common/string_helper.h"
#include "../common/datetime_helper.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace cc {
  void
  CCGenerator::GenerateClient (
    ::org::labcrypto::hottentot::generator::Hot *hot,
     ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig
  ) {
    std::string indent = generationConfig.GetIndentString();
    ::org::labcrypto::hottentot::generator::Os::MakeDir(generationConfig.GetOutDir() + "/client");
    for (uint32_t moduleCounter = 0; moduleCounter < hot->modules_.size(); moduleCounter++) {
      for (uint32_t serviceCounter = 0; serviceCounter < hot->modules_[moduleCounter]->services_.size(); serviceCounter++) {
        ::org::labcrypto::hottentot::generator::Service *service = hot->modules_[moduleCounter]->services_[serviceCounter];
        /*
         * Making real values
         */
        std::string serviceNameCamelCaseFirstCapital = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstCapital (
            service->GetName()
          ) + "Service";
        std::string serviceNameSnakeCase = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeSnakeCaseFromCamelCase (
            serviceNameCamelCaseFirstCapital
          );
        std::string clientFilePath = generationConfig.GetOutDir() + "/client/" + serviceNameSnakeCase + "_client.cc";
        std::string includeStructHeaders = "";
        for (uint32_t i = 0; i < service->module_->structs_.size(); i++) {
          includeStructHeaders += "#include \"../" + 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeSnakeCaseFromCamelCase (
              service->module_->structs_[i]->GetName()
            ) + ".h\"\r\n";
        }
        includeStructHeaders = ::org::labcrypto::hottentot::generator::StringHelper::Trim(includeStructHeaders);
        /*
         * Filling templates with real values
         */
        std::map<std::string, std::string> params;
        params.insert(std::pair<std::string, std::string>("GENERATION_DATE", ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime()));
        params.insert(std::pair<std::string, std::string>("FILENAME", serviceNameSnakeCase + "_client.h"));
        params.insert(std::pair<std::string, std::string>("NAMESPACE","::" + 
          ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
            ::org::labcrypto::hottentot::generator::StringHelper::Split (
              service->module_->GetPackage(), 
              '.'
            ), 
            "::"
          )
        ));
        params.insert(std::pair<std::string, std::string>("CAMEL_CASE_FC_SERVICE_NAME", serviceNameCamelCaseFirstCapital));
        params.insert(std::pair<std::string, std::string>("SNAKE_CASE_SERVICE_NAME", serviceNameSnakeCase));
        params.insert(std::pair<std::string, std::string>("INCLUDE_STRUCT_HEADERS", includeStructHeaders));
        params.insert(std::pair<std::string, std::string>("INDENT", indent));
        std::string clientTemplate((char *)__cc_templates_client_template, __cc_templates_client_template_len);
        // ::org::labcrypto::hottentot::generator::Os::ReadFile("cc/templates/client.template", clientTemplate);
        for (std::map<std::string, std::string>::iterator it = params.begin();
             it != params.end();
             ++it) {
          clientTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              clientTemplate, 
              "[[[" + it->first + "]]]", 
              it->second
            );
        }
        /*
         * Writing final results to files
         */
        std::fstream f;
        f.open(clientFilePath.c_str(), std::fstream::out | std::fstream::binary);
        f << clientTemplate;
        f.close();
      }
    }
  }
}
}
}
}
}