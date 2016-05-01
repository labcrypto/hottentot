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
  CCGenerator::GenerateRequestHandlerCC (
    ::org::labcrypto::hottentot::generator::Service *service,
    ::naeem::hottentot::generator::GenerationConfig &generationConfig,
    std::map<std::string, std::string> &templates
  ) {
    std::string indent = generationConfig.GetIndentString();
    /*
     * Making needed variables and assigning values to them
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
    std::string requestHandlerCCFilePath = generationConfig.GetOutDir() + "/service/" + 
      serviceNameSnakeCase + "_request_handler.cc";
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
     std::vector<std::string> packageTokens = 
      ::org::labcrypto::hottentot::generator::StringHelper::Split (
        service->module_->GetPackage(), 
        '.'
      );
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
    std::string methodIfClauses = "";
    for (uint32_t i = 0; i < service->methods_.size(); i++) {
      ::org::labcrypto::hottentot::generator::Method *method = service->methods_[i];
      methodIfClauses += 
        GenerateRequestHandlerCCMethodIfClause(service, method, generationConfig, templates) + "\r\n";
    }
    methodIfClauses = ::org::labcrypto::hottentot::generator::StringHelper::Trim(methodIfClauses);
    /*
     * Filling templates with real values
     */
    std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("GENERATION_DATE", 
      ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime()));
    params.insert(std::pair<std::string, std::string>("FILENAME", serviceNameSnakeCase + "_request_handler.cc"));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_START", namespacesStart));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_END", namespacesEnd));
    params.insert(std::pair<std::string, std::string>("INCLUDE_STRUCT_HEADERS", includeStructHeaders));
    params.insert(std::pair<std::string, std::string>("METHOD_IF_CLAUSES", methodIfClauses));
    params.insert(std::pair<std::string, std::string>("NAMESPACE","::" + 
      ::org::labcrypto::hottentot::generator::StringHelper::Concat( 
        ::org::labcrypto::hottentot::generator::StringHelper::Split(
            service->module_->GetPackage(), '.'), "::")));
    params.insert(std::pair<std::string, std::string>("CAMEL_CASE_FC_SERVICE_NAME", 
      serviceNameCamelCaseFirstCapital));
    params.insert(std::pair<std::string, std::string>("SNAKE_CASE_SERVICE_NAME", 
      serviceNameSnakeCase));
    params.insert(std::pair<std::string, std::string>("SCREAMING_SNAKE_CASE_SERVICE_NAME", 
      serviceNameScreamingSnakeCase));
    params.insert(std::pair<std::string, std::string>("INDENT", indent));
    std::string requestHandlerCCTemplate = templates["request_handler_cc"];
    for (std::map<std::string, std::string>::iterator it = params.begin();
         it != params.end();
         ++it) {
      requestHandlerCCTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          requestHandlerCCTemplate, 
          "[[[" + it->first + "]]]", 
          it->second
        );
    }
    /*
     * Writing final results to files
     */
    std::fstream f;
    f.open(requestHandlerCCFilePath.c_str(), std::fstream::out | std::fstream::binary);
    f << requestHandlerCCTemplate;
    f.close();
  }
  std::string 
  CCGenerator::GenerateRequestHandlerCCMethodIfClause (
    ::org::labcrypto::hottentot::generator::Service *service,
    ::org::labcrypto::hottentot::generator::Method *method,
    ::naeem::hottentot::generator::GenerationConfig &generationConfig,
    std::map<std::string, std::string> &templates
  ) {
    std::string indent = generationConfig.GetIndentString();
    /*
     * Making real values
     */
    std::string serviceNameCamelCaseFirstCapital = 
      ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstCapital (
        service->GetName()
      ) + "Service";
    std::stringstream methodHashSS;
    methodHashSS << method->GetHash();
    std::string ns = "::" + 
      ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
        ::org::labcrypto::hottentot::generator::StringHelper::Split (
          service->module_->GetPackage(), 
          '.'
        ), 
        "::"
      );
    std::string inputVariables = "";
    for (uint32_t i = 0; i < method->arguments_.size(); i++) {
      if (TypeHelper::IsUDT(method->arguments_[i]->GetType())) {
        inputVariables += indent + indent + indent + 
          TypeHelper::GetCCType(method->arguments_[i]->GetType(), ns) + 
            " " + method->arguments_[i]->GetVariable() + ";\r\n";
      } else {
        inputVariables += indent + indent + indent + 
          TypeHelper::GetCCType(method->arguments_[i]->GetType(), ns) + 
            " " + method->arguments_[i]->GetVariable() + ";\r\n";
      }
      std::stringstream tempSS;
      tempSS << ".Deserialize(request.GetArgumentData(" << i << "), request.GetArgumentLength(" << i << "));";
      inputVariables += indent + indent + indent + method->arguments_[i]->GetVariable() + tempSS.str() + "\r\n";
    }
    std::string methodCall;
    if (!TypeHelper::IsVoid(method->GetReturnType())) {
      methodCall += indent + indent + indent + TypeHelper::GetCCType(method->GetReturnType(), ns) + " result;\r\n";
    } 
    methodCall += indent + indent + indent + "try {\r\n";
    methodCall += indent + indent + indent + indent + "serviceObject->" + 
      ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(method->GetName()) + "(";
    std::string sep = "";
    for (uint32_t i = 0; i < method->arguments_.size(); i++) {
      methodCall += sep + method->arguments_[i]->GetVariable();
      sep = ", ";
    }
    if (!TypeHelper::IsVoid(method->GetReturnType())) {
      methodCall += sep + "result";
      sep = ", ";
    }
    methodCall += sep + "hotContext";
    methodCall += ");";
    for (uint32_t i = 0; i < method->arguments_.size(); i++) {
      if (TypeHelper::IsList(method->arguments_[i]->GetType())) {
        methodCall += indent + indent + indent + method->arguments_[i]->GetVariable() + ".Purge();\r\n";
      }
    }          
    std::string resultSerialization = "";
    resultSerialization += indent + indent + indent + "if (hotContext.GetResponseStatusCode() == 0) {\r\n";
    if (TypeHelper::IsVoid(method->GetReturnType())) {
      resultSerialization += indent + indent + indent + indent + "serializedData = 0;\r\n";
    } else {
      resultSerialization += indent + indent + indent + indent + 
        "serializedData = result.Serialize(&serializedDataLength);\r\n";
      if (!TypeHelper::IsVoid(method->GetReturnType())) {
        if (TypeHelper::IsList(method->GetReturnType())) {
          resultSerialization += indent + indent + indent + "result.Purge();\r\n";
        }
      }
    }
    resultSerialization += indent + indent + indent + "} else {\r\n";
    resultSerialization += indent + indent + indent + indent + 
      "::naeem::hottentot::runtime::types::Utf8String faultMessage(hotContext.GetFaultMessage());\r\n";
    resultSerialization += indent + indent + indent + indent + 
      "serializedData = faultMessage.Serialize(&serializedDataLength);\r\n";
    resultSerialization += indent + indent + indent + "}\r\n";
    /*
     * Filling template
     */
    std::string proxyCCMethodIfClauseTemplate = templates["request_handler_cc__method_if_clause"];
    proxyCCMethodIfClauseTemplate =
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        proxyCCMethodIfClauseTemplate,
        "[[[INDENT]]]",
        indent
      );
    proxyCCMethodIfClauseTemplate =
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        proxyCCMethodIfClauseTemplate,
        "[[[CAMEL_CASE_FC_SERVICE_NAME]]]",
        serviceNameCamelCaseFirstCapital
      );
    proxyCCMethodIfClauseTemplate =
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        proxyCCMethodIfClauseTemplate,
        "[[[METHOD_NAME]]]",
        ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(
          method->GetName()
        )
      );
    proxyCCMethodIfClauseTemplate =
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        proxyCCMethodIfClauseTemplate,
        "[[[INPUT_VARIABLES]]]",
        inputVariables
      );
    proxyCCMethodIfClauseTemplate =
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        proxyCCMethodIfClauseTemplate,
        "[[[RESULT_SERIALIZATION]]]",
        resultSerialization
      );
    proxyCCMethodIfClauseTemplate =
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        proxyCCMethodIfClauseTemplate,
        "[[[METHOD_CALL]]]",
        methodCall
      );
    proxyCCMethodIfClauseTemplate =
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        proxyCCMethodIfClauseTemplate,
        "[[[METHOD_HASH]]]",
        methodHashSS.str()
      );
    return proxyCCMethodIfClauseTemplate;
  }
}
}
}
}
}