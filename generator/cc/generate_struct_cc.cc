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

#include "../hot.h"
#include "../service.h"
#include "../method.h"
#include "../module.h"
#include "../argument.h"
#include "../struct.h"
#include "../declaration.h"
#include "../os.h"
#include "../string_helper.h"
#include "../datetime_helper.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace cc {
  void
  CCGenerator::GenerateStructCC (
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
    ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCaseFromCamelCase(structNameSnakeCase);
    std::string ns = "::" + 
      ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
        ::org::labcrypto::hottentot::generator::StringHelper::Split (
          structt->module_->GetPackage(), 
          '.'
        ), 
        "::"
      );
    std::string structCCFilePath = generationConfig.GetOutDir() + "/" + structNameSnakeCase + ".cc";
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
    std::string fields = "";
    /*
     * Serializarion
     */
    uint32_t counter = 0;
    std::stringstream serializationSS;
    serializationSS << indent << indent << "uint32_t totalLength = 0;\r\n";
    for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it = 
           structt->declarations_.begin();
         it != structt->declarations_.end();
         ++it) {
      serializationSS << indent << indent << "uint32_t length" << counter << " = 0;\r\n";
      // serializationSS << indent << indent << "unsigned char *data" << counter << " = ";
      serializationSS << indent << indent << 
        "::org::labcrypto::hottentot::runtime::HotPtr<unsigned char, true> ptr" << counter << ";\r\n";
      if (TypeHelper::IsUDT(it->second->GetType()) && !TypeHelper::IsList(it->second->GetType())) {
        serializationSS << indent << indent << "if (" << 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall(it->second->GetVariable()) + 
            "_" << ") {\r\n";
        serializationSS << indent << indent << indent << "ptr" << counter << " = ";
        serializationSS << 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
            it->second->GetVariable()
          ) + "_";
        serializationSS << "->";
        serializationSS << "Serialize(&length" << counter << ");\r\n";
        serializationSS << indent << indent << "}\r\n";
      } else {
        serializationSS << indent << indent << "ptr" << counter << " = ";
        serializationSS << 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
            it->second->GetVariable()
          ) + "_";
        serializationSS << ".";
        serializationSS << "Serialize(&length" << counter << ");\r\n";
      }
      if (TypeHelper::IsFixedLength(it->second->GetType())) {
        serializationSS << indent << indent << "totalLength += length" << counter << ";\r\n";
      } else {
        serializationSS << indent << indent << "if (length" << counter << " < 128) {\r\n";
        serializationSS << indent << indent << indent << "totalLength += 1 + length" << counter << ";\r\n";
        serializationSS << indent << indent << "} else if (length" << counter << " < 256) {\r\n";
        serializationSS << indent << indent << indent << "totalLength += 2 + length" << counter << ";\r\n";
        serializationSS << indent << indent << "} else if (length" << counter << " < 256 * 256) {\r\n";
        serializationSS << indent << indent << indent << "totalLength += 3 + length" << counter << ";\r\n";
        serializationSS << indent << indent << "} else if (length" << counter << " < 256 * 256 * 256) {\r\n";
        serializationSS << indent << indent << indent << "totalLength += 4 + length" << counter << ";\r\n";
        serializationSS << indent << indent << "}\r\n";
      }
      counter++;
    }
    serializationSS << indent << indent << "unsigned char *data = new unsigned char[totalLength];\r\n";
    serializationSS << indent << indent << "uint32_t c = 0;\r\n";
    counter = 0;
    for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it = 
           structt->declarations_.begin();
         it != structt->declarations_.end();
         ++it) {
      if (!TypeHelper::IsFixedLength(it->second->GetType())) {
        serializationSS << indent << indent << "if (length" << counter << " < 128) {\r\n";
        serializationSS << indent << indent << indent << "data[c] = length" << counter << ";\r\n";
        serializationSS << indent << indent << indent << "c += 1;\r\n";
        serializationSS << indent << indent << "} else if (length" << counter << " < 256) {\r\n";
        serializationSS << indent << indent << indent << "data[c] = 0x81;\r\n";
        serializationSS << indent << indent << indent << "data[c + 1] = length" << counter << ";\r\n";
        serializationSS << indent << indent << indent << "c += 2;\r\n";
        serializationSS << indent << indent << "} else if (length" << counter << " < 256 * 256) {\r\n";
        serializationSS << indent << indent << indent << "data[c] = 0x82;\r\n";
        serializationSS << indent << indent << indent << "data[c + 1] = length" << counter << " / 256;\r\n";
        serializationSS << indent << indent << indent << "data[c + 2] = length" << counter << " % 256;\r\n";
        serializationSS << indent << indent << indent << "c += 3;\r\n";
        serializationSS << indent << indent << "} else if (length" << counter << " < 256 * 256 * 256) {\r\n";
        serializationSS << indent << indent << indent << "data[c] = 0x83;\r\n";
        serializationSS << indent << indent << indent << "data[c + 1] = length" << counter << " / (256 * 256);\r\n";
        serializationSS << indent << indent << indent << "data[c + 2] = (length" << counter << " - data[c + 1] * (256 * 256)) / 256;\r\n";
        serializationSS << indent << indent << indent << "data[c + 3] = length" << counter << " % (256 * 256);\r\n";
        serializationSS << indent << indent << indent << "c += 4;\r\n";
        serializationSS << indent << indent << "}\r\n";
      }
      serializationSS << indent << indent << "unsigned char *data" << counter << " = ptr" << counter << ".Get();\r\n";
      serializationSS << indent << indent << "for (uint32_t i = 0; i < length" << counter << "; i++) {\r\n";
      serializationSS << indent << indent << indent << "data[c++] = data" << counter << "[i];\r\n";
      serializationSS << indent << indent << "}\r\n";
      counter++;
    }
    serializationSS << indent << indent << "if (c != totalLength) {\r\n";
    serializationSS << indent << indent << indent << 
      "std::cout << \"Struct Serialization: Inconsistency in length of serialized byte array.\" << std::endl;\r\n";
    serializationSS << indent << indent << indent << "exit(1);\r\n";
    serializationSS << indent << indent << "};\r\n";
    serializationSS << indent << indent << "if (length_ptr) {\r\n";
    serializationSS << indent << indent << indent << "*length_ptr = totalLength;\r\n";
    serializationSS << indent << indent << "}\r\n";
    serializationSS << indent << indent << "return data;\r\n";
    std::string serialization = serializationSS.str();
    /*
     * Deserialization
     */
    bool hasAnyVariableLengthField = false;
    for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it = 
           structt->declarations_.begin();
         it != structt->declarations_.end();
         ++it) {
      if (!TypeHelper::IsFixedLength(it->second->GetType())) {
        hasAnyVariableLengthField = true;
      }
    }
    std::stringstream deserializationSS;
    deserializationSS << indent << indent << "uint32_t c = 0";
    if (hasAnyVariableLengthField) {
      deserializationSS << ", elength = 0;\r\n";
    } else {
      deserializationSS << ";\r\n";
    }
    for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it = 
           structt->declarations_.begin();
         it != structt->declarations_.end();
         ++it) {
      if (TypeHelper::IsFixedLength(it->second->GetType())) {
        deserializationSS << indent << indent << 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
            it->second->GetVariable()
          ) + "_";
        if (TypeHelper::IsUDT(it->second->GetType()) && !TypeHelper::IsList(it->second->GetType())) {
          deserializationSS << "->";
        } else {
          deserializationSS << ".";
        }
        deserializationSS << "Deserialize(data + c, " << 
          TypeHelper::GetFixedLength(it->second->GetType()) << ");\r\n";
        deserializationSS << indent << indent << "c += " << 
          TypeHelper::GetFixedLength(it->second->GetType()) << ";\r\n";
      } else {
        deserializationSS << indent << indent << "if ((data[c] & 0x80) == 0) {\r\n";
        deserializationSS << indent << indent << indent << "elength = data[c];\r\n";
        deserializationSS << indent << indent << indent << "c++;\r\n";
        deserializationSS << indent << indent << "} else {\r\n";
        deserializationSS << indent << indent << indent << "uint8_t ll = data[c] & 0x0f;\r\n";
        deserializationSS << indent << indent << indent << "c++;\r\n";
        deserializationSS << indent << indent << indent << "if (ll == 1) {\r\n";
        deserializationSS << indent << indent << indent << indent << "elength = data[c];\r\n";
        deserializationSS << indent << indent << indent << indent << "c += 1;\r\n";
        deserializationSS << indent << indent << indent << "} else if (ll == 2) {\r\n";
        deserializationSS << indent << indent << indent << indent << "elength = data[c] * 256 + data[c + 1];\r\n";
        deserializationSS << indent << indent << indent << indent << "c += 2;\r\n";
        deserializationSS << indent << indent << indent << "} else if (ll == 3) {\r\n";
        deserializationSS << indent << indent << indent << indent << "elength = data[c] * 256 * 256 + data[c + 1] * 256 + data[c + 2];\r\n";
        deserializationSS << indent << indent << indent << indent << "c += 3;\r\n";
        deserializationSS << indent << indent << indent << "}\r\n";
        deserializationSS << indent << indent << "}\r\n";
        
        if (TypeHelper::IsUDT(it->second->GetType()) && !TypeHelper::IsList(it->second->GetType())) {
          deserializationSS << indent << indent << "if (elength > 0) {\r\n";
          deserializationSS << indent << indent << indent << 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall(it->second->GetVariable()) << 
              "_ = new " << TypeHelper::GetCCType(it->second->GetType(), ns) << ";\r\n";
          deserializationSS << indent << indent << indent << 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall(it->second->GetVariable()) + "_";
          deserializationSS << "->";
          deserializationSS << "Deserialize(data + c, elength);\r\n";
          deserializationSS << indent << indent << "} else {\r\n";
          deserializationSS << indent << indent << indent << 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall(it->second->GetVariable()) + 
              "_ = NULL;\r\n";
          deserializationSS << indent << indent << "}\r\n";
        } else {
          deserializationSS << indent << indent << 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall(it->second->GetVariable()) + "_";
          deserializationSS << ".";
          deserializationSS << "Deserialize(data + c, elength);\r\n";
        }
        deserializationSS << indent << indent << "c += elength;\r\n";
      }
    }
    deserializationSS << indent << indent << "if (c != length) {\r\n";
    deserializationSS << indent << indent << indent << 
      "std::cout << \"Struct Deserialization: Inconsistency in length of deserialized byte array.\" << std::endl;\r\n";
    deserializationSS << indent << indent << indent << "exit(1);\r\n";
    deserializationSS << indent << indent << "};\r\n";
    std::string deserialization = deserializationSS.str();
    /*
     * Ctor assignments
     */
    std::string copyCtorAssign = "";
    for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it = 
           structt->declarations_.begin();
         it != structt->declarations_.end();
         ++it) {
      copyCtorAssign += indent + indent + 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
          it->second->GetVariable()
        ) + "_";
      copyCtorAssign += " = other." + 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall (
          it->second->GetVariable()
        ) + "_;\r\n";
    }
    std::string pointerCtorAssign = "";
    for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it = 
           structt->declarations_.begin();
         it != structt->declarations_.end();
         ++it) {
      pointerCtorAssign += indent + indent + 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall(it->second->GetVariable()) + "_";
      pointerCtorAssign += " = other->" + 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstSmall(it->second->GetVariable()) + 
          "_;\r\n";
    }
    /*
     * Filling templates with real values
     */
    std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("GENERATION_DATE", 
      ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime()));
    params.insert(std::pair<std::string, std::string>("FILENAME", structNameSnakeCase + ".cc"));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_START", namespacesStart));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_END", namespacesEnd));
    params.insert(std::pair<std::string, std::string>("NAMESPACE","::" + 
      ::org::labcrypto::hottentot::generator::StringHelper::Concat( 
        ::org::labcrypto::hottentot::generator::StringHelper::Split(
            structt->module_->GetPackage(), '.'), "::")));
    params.insert(std::pair<std::string, std::string>("STRUCT_NAME", structNameCamelCaseFirstCapital));
    params.insert(std::pair<std::string, std::string>("SNAKE_CASE_STRUCT_NAME", structNameSnakeCase));
    params.insert(std::pair<std::string, std::string>("COPY_CTOR_ASSIGN", copyCtorAssign));
    params.insert(std::pair<std::string, std::string>("POINTER_CTOR_ASSIGN", pointerCtorAssign));
    params.insert(std::pair<std::string, std::string>("SERIALIZATION", serialization));
    params.insert(std::pair<std::string, std::string>("DESERIALIZATION", deserialization));
    params.insert(std::pair<std::string, std::string>("INDENT", indent));
    std::string structCCTemplate = templates["struct_cc"];
    for (std::map<std::string, std::string>::iterator it = params.begin();
         it != params.end();
         ++it) {
      structCCTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          structCCTemplate, 
          "[[[" + it->first + "]]]", 
          it->second
        );
    }
    /*
     * Writing final results to files
     */
    std::fstream f;
    f.open(structCCFilePath.c_str(), std::fstream::out | std::fstream::binary);
    f << structCCTemplate;
    f.close();
  }
}
}
}
}
}