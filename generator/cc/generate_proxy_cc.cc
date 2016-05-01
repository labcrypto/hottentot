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
  CCGenerator::GenerateProxyCC (
    ::org::labcrypto::hottentot::generator::Service *service,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig,
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
      ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCaseFromCamelCase(serviceNameSnakeCase);
    std::string serviceProxyHeaderFilePath = generationConfig.GetOutDir() + "/proxy/" + 
      serviceNameSnakeCase + "_proxy.h";
    std::string serviceProxyCCFilePath = generationConfig.GetOutDir() + "/proxy/" + 
      serviceNameSnakeCase + "_proxy.cc";
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
      namespacesEnd += "}  // END OF NAMESPACE " + packageTokens[i] + "\r\n";
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
    std::string methods = "";
    for (uint32_t i = 0; i < service->methods_.size(); i++) {
      ::org::labcrypto::hottentot::generator::Method *method = service->methods_[i];
      methods += GenerateProxyCCMethod(service, method, generationConfig, templates) + "\r\n";
    }
    /*
     * Filling templates with real values
     */
    std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("GENERATION_DATE", 
      ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime()));
    params.insert(std::pair<std::string, std::string>("FILENAME", serviceNameSnakeCase + "_proxy.cc"));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_START", namespacesStart));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_END", namespacesEnd));
    params.insert(std::pair<std::string, std::string>("INCLUDE_STRUCT_HEADERS", includeStructHeaders));
    params.insert(std::pair<std::string, std::string>("HEADER_GUARD", "_" +
      ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCase (
        packageTokens
      ) + "__PROXY__" + serviceNameScreamingSnakeCase + "_PROXY_H_"));
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
    params.insert(std::pair<std::string, std::string>("SNAKE_CASE_SERVICE_NAME", 
      serviceNameSnakeCase));
    params.insert(std::pair<std::string, std::string>("SCREAMING_SNAKE_CASE_SERVICE_NAME", 
      serviceNameScreamingSnakeCase));
    params.insert(std::pair<std::string, std::string>("METHODS", methods));
    params.insert(std::pair<std::string, std::string>("INDENT", indent));
    std::string proxyCCTemplate = templates["proxy_cc"];
    for (std::map<std::string, std::string>::iterator it = params.begin();
         it != params.end();
         ++it) {
      proxyCCTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace(
          proxyCCTemplate, 
          "[[[" + it->first + "]]]", 
          it->second
        );
    }
    /*
     * Writing final results to files
     */
    std::fstream f;
    f.open(serviceProxyCCFilePath.c_str(), std::fstream::out | std::fstream::binary);
    f << proxyCCTemplate;
    f.close();
  }
  std::string
  CCGenerator::GenerateProxyCCMethod (
    ::org::labcrypto::hottentot::generator::Service *service,
    ::org::labcrypto::hottentot::generator::Method *method,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig,
    std::map<std::string, std::string> &templates
  ) {
    std::string indent = generationConfig.GetIndentString();
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
    std::string arguments = "";
    for (uint32_t j = 0; j < method->arguments_.size(); j++) {
      arguments += indent + indent + indent + 
        TypeHelper::GetCCType(method->arguments_[j]->GetType(), ns) + 
          " &" + method->arguments_[j]->GetVariable();
      if (j == (method->arguments_.size() - 1)) {
          if (!TypeHelper::IsVoid(method->GetReturnType())) {
            arguments += ", ";
          }
        } else {
          arguments += ", ";
        }
        arguments += "\r\n";
    }
    if (!TypeHelper::IsVoid(method->GetReturnType())) {
      arguments += indent + indent + indent + 
        TypeHelper::GetCCType(method->GetReturnType(), ns) + " &out\r\n";
    }
    std::string argumentsSerialization = "";
    if (method->arguments_.size() > 0) {
      argumentsSerialization += indent + indent + "uint32_t serializedDataLength = 0;\r\n";
      argumentsSerialization += indent + indent + "unsigned char *serializedData = 0;\r\n";
    }
    for (uint32_t j = 0; j < method->arguments_.size(); j++) {
      std::string proxyCCMethodArgumentSerializationTemplate = templates["proxy_cc__method_argument_serialization"];
      proxyCCMethodArgumentSerializationTemplate =
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodArgumentSerializationTemplate,
          "[[[ARGUMENT_NAME]]]",
          method->arguments_[j]->GetVariable()
        );
      proxyCCMethodArgumentSerializationTemplate =
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodArgumentSerializationTemplate,
          "[[[INDENT]]]",
          indent
        );
      proxyCCMethodArgumentSerializationTemplate =
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodArgumentSerializationTemplate,
          "[[[ACCESS_OPERATOR]]]",
          "."
        );
      argumentsSerialization += proxyCCMethodArgumentSerializationTemplate + "\r\n";
    }
    std::string responseDeserialization = "";
    if (!TypeHelper::IsVoid(method->GetReturnType())) {
      responseDeserialization += indent + indent + indent + "/*\r\n";
      responseDeserialization += indent + indent + indent + " * Response deserialization\r\n";
      responseDeserialization += indent + indent + indent + " */\r\n";
      std::string proxyCCMethodResponseDeserializationTemplate = templates["proxy_cc__method_response_deserialization"];
      proxyCCMethodResponseDeserializationTemplate =
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodResponseDeserializationTemplate,
          "[[[RETURN_TYPE]]]",
          TypeHelper::GetCCType(method->GetReturnType(), ns)
        );
      proxyCCMethodResponseDeserializationTemplate =
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodResponseDeserializationTemplate,
          "[[[INDENT]]]",
          indent
        );
      proxyCCMethodResponseDeserializationTemplate =
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodResponseDeserializationTemplate,
          "[[[ACCESS_OPERATOR]]]",
          "."
        );
      proxyCCMethodResponseDeserializationTemplate =
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodResponseDeserializationTemplate,
          "[[[POINTER_SIGN]]]",
          "*"
        );
      responseDeserialization += proxyCCMethodResponseDeserializationTemplate + "\r\n";
    }
    std::stringstream serviceHashSS;
    serviceHashSS << service->GetHash();
    std::stringstream methodHashSS;
    methodHashSS << method->GetHash();
    /*
     * Filling templates with real values
     */
    std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("RETURN_TYPE", 
      TypeHelper::IsVoid(method->GetReturnType()) ? "void" : 
        TypeHelper::GetCCType(method->GetReturnType(), ns) + "*"));
    params.insert(std::pair<std::string, std::string>("CAMEL_CASE_FC_SERVICE_NAME", 
      serviceNameCamelCaseFirstCapital));
    params.insert(std::pair<std::string, std::string>("METHOD_NAME", 
      ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(method->GetName())));
    params.insert(std::pair<std::string, std::string>("ARGUMENTS", arguments));
    params.insert(std::pair<std::string, std::string>("ARGUMENTS_SERIALIZATION", argumentsSerialization));
    params.insert(std::pair<std::string, std::string>("RESPONSE_DESERIALIZATION", responseDeserialization));
    params.insert(std::pair<std::string, std::string>("SERVICE_HASH", serviceHashSS.str()));
    params.insert(std::pair<std::string, std::string>("METHOD_HASH", methodHashSS.str()));
    params.insert(std::pair<std::string, std::string>("INDENT", indent));
    std::string proxyCCMethodTemplate = templates["proxy_cc__method"];
    for (std::map<std::string, std::string>::iterator it = params.begin();
         it != params.end();
         ++it) {
      proxyCCMethodTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          proxyCCMethodTemplate, 
          "[[[" + it->first + "]]]", 
          it->second
        );
    }
    return proxyCCMethodTemplate;
  }
  std::string
  CCGenerator::GenerateProxyCCMethodArgumentSerialization (
    ::org::labcrypto::hottentot::generator::Service *service,
    ::org::labcrypto::hottentot::generator::Method *method,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig,
    std::map<std::string, std::string> &templates
  ) {
    // TODO
    return "";
  }
}
}
}
}
}