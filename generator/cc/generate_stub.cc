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
  CCGenerator::GenerateStub (
    ::org::labcrypto::hottentot::generator::Hot *hot,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig
  ) {
    std::string indent = generationConfig.GetIndentString();
    ::org::labcrypto::hottentot::generator::Os::MakeDir(generationConfig.GetOutDir() + "/stub");
    for (uint32_t moduleCounter = 0; moduleCounter < hot->modules_.size(); moduleCounter++) {
      for (uint32_t serviceCounter = 0; 
           serviceCounter < hot->modules_[moduleCounter]->services_.size(); 
           serviceCounter++) {
        ::org::labcrypto::hottentot::generator::Service *service = 
          hot->modules_[moduleCounter]->services_[serviceCounter];
        std::string ns = "::" + 
          ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
            ::org::labcrypto::hottentot::generator::StringHelper::Split (
              service->module_->GetPackage(), 
              '.'
            ), 
            "::"
          );
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
        std::string serviceNameScreamingSnakeCase =
          ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCaseFromCamelCase (
            serviceNameSnakeCase
          );
        std::string implHeaderFilePath = generationConfig.GetOutDir() + "/stub/" + serviceNameSnakeCase + "_impl.h";
        std::string implCCFilePath = generationConfig.GetOutDir() + "/stub/" + serviceNameSnakeCase + "_impl.cc";
        std::string serverFilePath = generationConfig.GetOutDir() + "/stub/" + serviceNameSnakeCase + "_server.cc";
        std::vector<std::string> packageTokens = ::org::labcrypto::hottentot::generator::StringHelper::Split(
          service->module_->GetPackage(), '.');
        std::string namespacesStart = "";
        for (uint32_t i = 0; i < packageTokens.size(); i++) {
          namespacesStart += "namespace " + 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeLowerCase(packageTokens[i]) + " {\r\n";
        }
        std::string namespacesEnd = "";
        for (int32_t i = packageTokens.size() - 1; i >= 0; i--) {
          namespacesEnd += "} // END OF NAMESPACE " + packageTokens[i] + "\r\n";
        }
        std::string includeStructHeaders = "";
        for (uint32_t i = 0; i < service->module_->structs_.size(); i++) {
          includeStructHeaders += "#include \"../" + 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeSnakeCaseFromCamelCase (
              service->module_->structs_[i]->GetName()
            ) + ".h\"\r\n";
        }
        namespacesStart = ::org::labcrypto::hottentot::generator::StringHelper::Trim(namespacesStart);
        namespacesEnd = ::org::labcrypto::hottentot::generator::StringHelper::Trim(namespacesEnd);
        includeStructHeaders = ::org::labcrypto::hottentot::generator::StringHelper::Trim(includeStructHeaders);
        std::string methodDefs = "";
        for (uint32_t i = 0; i < service->methods_.size(); i++) {
          ::org::labcrypto::hottentot::generator::Method *method = service->methods_[i];
          methodDefs += indent + indent + "virtual void " + 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(method->GetName()) + "(\r\n";
          for (uint32_t j = 0; j < method->arguments_.size(); j++) {
            methodDefs += indent + indent + indent + 
              TypeHelper::GetCCType(method->arguments_[j]->GetType(), ns) + " &" + 
                method->arguments_[j]->GetVariable() + ", \r\n";
          }
          if (!TypeHelper::IsVoid(method->GetReturnType())) {
            methodDefs += indent + indent + indent + 
              TypeHelper::GetCCType(method->GetReturnType(), ns) + " &out, \r\n";
          }
          methodDefs += indent + indent + indent + 
            "::org::labcrypto::hottentot::runtime::service::HotContext &hotContext\r\n";
          methodDefs += indent + indent + ");\r\n";
        }
        methodDefs = ::org::labcrypto::hottentot::generator::StringHelper::Trim(methodDefs);
        std::string methods = "";
        for (uint32_t i = 0; i < service->methods_.size(); i++) {
          ::org::labcrypto::hottentot::generator::Method *method = service->methods_[i];
          std::string arguments = "";
          for (uint32_t j = 0; j < method->arguments_.size(); j++) {
            arguments += indent + indent + indent + 
              TypeHelper::GetCCType(method->arguments_[j]->GetType(), ns) + " &" + 
                method->arguments_[j]->GetVariable() + ", \r\n";
          }
          if (!TypeHelper::IsVoid(method->GetReturnType())) {
            arguments += indent + indent + indent + 
              TypeHelper::GetCCType(method->GetReturnType(), ns) + " &out, \r\n";
          }
          arguments += indent + indent + indent + 
            "::org::labcrypto::hottentot::runtime::service::HotContext &hotContext\r\n";
          std::string methodTemplate (
            (char *)__cc_templates_service_impl_cc__method_template, 
            __cc_templates_service_impl_cc__method_template_len
          );
          methodTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              methodTemplate, 
              "[[[CAMEL_CASE_FC_SERVICE_NAME]]]", 
              serviceNameCamelCaseFirstCapital
            );
          methodTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              methodTemplate, 
              "[[[ARGUMENTS]]]", 
              arguments
            );
          methodTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              methodTemplate, 
              "[[[METHOD_NAME]]]", 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(method->GetName())
            );
          methodTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              methodTemplate, 
              "[[[RETURN_TYPE]]]", 
              TypeHelper::GetCCType(method->GetReturnType(), ns) + 
                (!TypeHelper::IsVoid(method->GetReturnType()) ? "*" : "")
            );
          methodTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              methodTemplate, 
              "[[[INDENT]]]", 
              indent
            );
          methods += methodTemplate + "\r\n";
        }
        /*
         * Filling templates with real values
         */
        std::map<std::string, std::string> params;
        params.insert(std::pair<std::string, std::string>("GENERATION_DATE", 
          ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime()));
        params.insert(std::pair<std::string, std::string>("FILENAME", serviceNameSnakeCase + "_impl.h"));
        params.insert(std::pair<std::string, std::string>("HEADER_GUARD", "_" +
          ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCase (
            packageTokens
          ) + "__" + serviceNameScreamingSnakeCase + "_IMPL_H_"));
        params.insert(std::pair<std::string, std::string>("NAMESPACE","::" + 
          ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
            ::org::labcrypto::hottentot::generator::StringHelper::Split (
              service->module_->GetPackage(), 
              '.'
            ), 
            "::"
          )
        ));
        params.insert(std::pair<std::string, std::string>("CAMEL_CASE_FC_SERVICE_NAME", 
          serviceNameCamelCaseFirstCapital));
        params.insert(std::pair<std::string, std::string>("SNAKE_CASE_SERVICE_NAME", serviceNameSnakeCase));
        params.insert(std::pair<std::string, std::string>("INCLUDE_STRUCT_HEADERS", includeStructHeaders));
        params.insert(std::pair<std::string, std::string>("NAMESPACES_START", namespacesStart));
        params.insert(std::pair<std::string, std::string>("NAMESPACES_END", namespacesEnd));
        params.insert(std::pair<std::string, std::string>("METHOD_DEFS", methodDefs));
        params.insert(std::pair<std::string, std::string>("METHODS", methods));
        params.insert(std::pair<std::string, std::string>("INDENT", indent));
        std::string implHeaderTemplate (
          (char *)__cc_templates_service_impl_header_template, 
          __cc_templates_service_impl_header_template_len
        );
        for (std::map<std::string, std::string>::iterator it = params.begin();
             it != params.end();
             ++it) {
          implHeaderTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              implHeaderTemplate, 
              "[[[" + it->first + "]]]", 
              it->second
            );
        }
        /*
         * Writing final results to files
         */
        std::fstream f;
        f.open(implHeaderFilePath.c_str(), std::fstream::out | std::fstream::binary);
        f << implHeaderTemplate;
        f.close();
        /*
         * Filling templates with real values
         */
        params["GENERATION_DATE"] = ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime();
        params["FILENAME"] = serviceNameSnakeCase + "_impl.cc";
        std::string implCCTemplate (
          (char *)__cc_templates_service_impl_cc_template,
          __cc_templates_service_impl_cc_template_len
        );
        for (std::map<std::string, std::string>::iterator it = params.begin();
             it != params.end();
             ++it) {
          implCCTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              implCCTemplate, 
              "[[[" + it->first + "]]]", 
              it->second
            );
        }
        /*
         * Writing final results to files
         */
        f.open(implCCFilePath.c_str(), std::fstream::out | std::fstream::binary);
        f << implCCTemplate;
        f.close();
        /*
         * Filling templates with real values
         */
        params["GENERATION_DATE"] = ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime();
        params["FILENAME"] = serviceNameSnakeCase + "_server.cc";
        std::string serverTemplate (
          (char *)__cc_templates_server_template, 
          __cc_templates_server_template_len
        );
        // ::org::labcrypto::hottentot::generator::Os::ReadFile("cc/templates/server.template", serverTemplate);
        for (std::map<std::string, std::string>::iterator it = params.begin();
             it != params.end();
             ++it) {
          serverTemplate = 
            ::org::labcrypto::hottentot::generator::StringHelper::Replace (
              serverTemplate, 
              "[[[" + it->first + "]]]", 
              it->second
            );
        }
        /*
         * Writing final results to files
         */
        f.open(serverFilePath.c_str(), std::fstream::out | std::fstream::binary);
        f << serverTemplate;
        f.close();
      }
    }          
  }
}
}
}
}
}