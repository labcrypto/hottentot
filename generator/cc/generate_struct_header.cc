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
  CCGenerator::GenerateStructHeader (
    ::org::labcrypto::hottentot::generator::Struct *structt,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig,
    std::map<std::string, std::string> &templates
  ) {
    std::string indent = generationConfig.GetIndentString();
    /*
     * Making needed variables and assigning values to them
     */
    std::string structNameCamelCaseFirstCapital = 
      ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstCapital (
        structt->GetName()
      );
    std::string structNameSnakeCase = 
      ::org::labcrypto::hottentot::generator::StringHelper::MakeSnakeCaseFromCamelCase (
        structNameCamelCaseFirstCapital
      );
    std::string structNameScreamingSnakeCase =
      ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCaseFromCamelCase (
        structNameSnakeCase
      );
    std::string structHeaderFilePath = generationConfig.GetOutDir() + "/" + structNameSnakeCase + ".h";
    std::string ns = "::" + 
      ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
        ::org::labcrypto::hottentot::generator::StringHelper::Split (
          structt->module_->GetPackage(), 
          '.'
        ), 
        "::"
      );
    /*
     * Making real values
     */
    std::vector<std::string> packageTokens = 
      ::org::labcrypto::hottentot::generator::StringHelper::Split (
        structt->module_->GetPackage(), 
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
    namespacesStart = ::org::labcrypto::hottentot::generator::StringHelper::Trim(namespacesStart);
    namespacesEnd = ::org::labcrypto::hottentot::generator::StringHelper::Trim(namespacesEnd);
    std::string initializations = "";
    std::string fields = "";
    std::string gettersAndSetters = "";
    std::vector<std::string> dependencies;
    for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it = 
           structt->declarations_.begin();
         it != structt->declarations_.end();
         ++it) {
      if (TypeHelper::IsUDT(it->second->GetType())) {
        if (TypeHelper::IsList(it->second->GetType())) {
          std::string listType = TypeHelper::GetTypeOfList(it->second->GetType());
          dependencies.push_back(listType);
        } else {
          dependencies.push_back(it->second->GetType());
        }
      }
      fields += indent + indent +  TypeHelper::GetCCType(it->second->GetType(), ns);
      if (TypeHelper::IsUDT(it->second->GetType()) && !TypeHelper::IsList(it->second->GetType())) {
        fields += "*";
        initializations += indent + indent + indent + 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
            it->second->GetVariable()
          ) + "_ = NULL;\r\n";
      }
      fields += " " + 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
          it->second->GetVariable()
        ) + "_";
      fields += ";\r\n";
      std::string getterAndSetterTemplate = templates["struct_header__getter_and_setter"];
      getterAndSetterTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          getterAndSetterTemplate,
          "[[[INDENT]]]",
          indent
        );
      getterAndSetterTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          getterAndSetterTemplate,
          "[[[TYPE]]]",
          TypeHelper::GetCCType(it->second->GetType(), ns) + 
          ((TypeHelper::IsUDT(it->second->GetType()) && 
            !TypeHelper::IsList(it->second->GetType())) ? "*" : ""
        )
      );
      getterAndSetterTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          getterAndSetterTemplate,
          "[[[CAMEL_CASE_FC_FIELD]]]",
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstCapital (
            it->second->GetVariable()
          )
        );
      getterAndSetterTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          getterAndSetterTemplate,
          "[[[CAMEL_CASE_FS_FIELD]]]",
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
            it->second->GetVariable()
          )
        );
        gettersAndSetters += getterAndSetterTemplate + "\r\n";
    }
    std::string includeDependencies = "";
    for (uint32_t i = 0; i < dependencies.size(); i++) {
      includeDependencies += "#include \"" + 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeSnakeCaseFromCamelCase(dependencies[i]) + ".h\"";
    }
    /*
     * Filling templates with real values
     */
    std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("GENERATION_DATE", 
      ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime()));
    params.insert(std::pair<std::string, std::string>("FILENAME", structNameSnakeCase + ".h"));
    params.insert(std::pair<std::string, std::string>("INCLUDE_DEPENDENCIES", includeDependencies));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_START", namespacesStart));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_END", namespacesEnd));
    params.insert(std::pair<std::string, std::string>("GETTERS_AND_SETTERS", gettersAndSetters));
    params.insert(std::pair<std::string, std::string>("HEADER_GUARD", "_" +
      ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCase(
        packageTokens) + "__" + structNameScreamingSnakeCase + "_H_"));
    params.insert(std::pair<std::string, std::string>("NAMESPACE","::" + 
      ::org::labcrypto::hottentot::generator::StringHelper::Concat( 
        ::org::labcrypto::hottentot::generator::StringHelper::Split(
            structt->module_->GetPackage(), '.'), "::")));
    params.insert(std::pair<std::string, std::string>("STRUCT_NAME", structNameCamelCaseFirstCapital));
    params.insert(std::pair<std::string, std::string>("FIELDS", fields));
    params.insert(std::pair<std::string, std::string>("INITIALIZATIONS", initializations));
    params.insert(std::pair<std::string, std::string>("INDENT", indent));
    std::string structHeaderTemplate = templates["struct_header"];
    for (std::map<std::string, std::string>::iterator it = params.begin();
         it != params.end();
         ++it) {
      structHeaderTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          structHeaderTemplate, 
          "[[[" + it->first + "]]]", 
          it->second
        );
    }
    /*
     * Writing final results to files
     */
    std::fstream f;
    f.open(structHeaderFilePath.c_str(), std::fstream::out | std::fstream::binary);
    f << structHeaderTemplate;
    f.close();
  }
}
}
}
}