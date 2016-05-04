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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANindent_ILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <sys/stat.h>

#include <sstream>

#include "java_generator.h"

#include "../hot.h"
#include "../string_helper.h"
#include "../os.h" 
#include "../type_helper.h" 


void 
GenerateSerializableStructListFile (
  ::org::labcrypto::hottentot::generator::Module *pModule,
  std::string listStructName ,
  std::string basePackageName ,
  std::string replacableSerializableStructListTmpStr ,
  std::string outDir ,
  std::string indent
) {
  std::string lowerCaseStructName = 
    ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstLowerCase(listStructName);
  std::string upperCaseStructName = 
    ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(listStructName);
  std::string serializableHottentotTypeName = 
    ::org::labcrypto::hottentot::generator::TypeHelper::GetSerializableHottentotType(listStructName);
  std::string lowerCaseSerializableHottentotTypeName = 
    ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstLowerCase(serializableHottentotTypeName);
  std::string javaClassType = 
    ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaClassType(listStructName);
  std::string instanciationHottentotTypeStr = "";
  std::string getValueMethodStr = "";
  if (!::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(listStructName)) {
    getValueMethodStr = ".getValue()";
  }
  if (!::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(listStructName)) {
    instanciationHottentotTypeStr = 
      serializableHottentotTypeName + " " +
      lowerCaseSerializableHottentotTypeName + " = " + 
      "new " + serializableHottentotTypeName + "( " + 
      lowerCaseStructName + 
      " );";
  }
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%BASE_PACKAGE_NAME%]",
    basePackageName,
    1
  );
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%INDENT%]", 
    indent ,
    1
  );
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%STRUCT_NAME%]",
    listStructName,
    1
  );
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%UPPER_CASE_STRUCT_NAME%]",
    upperCaseStructName,
    1
  );
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%LOWER_CASE_STRUCT_NAME%]",
    lowerCaseStructName,
    1
  );            
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%HOTTENTOT_TYPE%]",
    serializableHottentotTypeName,
    1
  );            
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%LOWER_CASE_HOTTENTOT_TYPE%]",
    lowerCaseSerializableHottentotTypeName,
    1
  );            
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%JAVA_CLASS_TYPE%]",
    javaClassType,
    1
  );            
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%INSTANCIATION_HOTTENTOT_TYPE%]",
    instanciationHottentotTypeStr,
    1
  );     
  ::org::labcrypto::hottentot::generator::StringHelper::Replace (
    replacableSerializableStructListTmpStr, 
    "[%GET_VALUE_METHOD%]",
    getValueMethodStr,
    1);     
  std::string packages =
    ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
      ::org::labcrypto::hottentot::generator::StringHelper::Split (
       pModule->GetPackage(), 
        '.'
      ), 
      "/"
    );
  ::org::labcrypto::hottentot::generator::Os::MakeDir(outDir + "/" + packages);   
  std::string path = outDir + "/" + packages + "/Serializable" + 
    upperCaseStructName.c_str() + "List.java";
  ::org::labcrypto::hottentot::generator::Os::WriteFile (
    path, 
    replacableSerializableStructListTmpStr
  );
}

namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  void
  JavaGenerator::GenerateSerializableStructList (
    ::org::labcrypto::hottentot::generator::Module *pModule
  ) {
    ::org::labcrypto::hottentot::generator::Service *pService;
    std::string basePackageName = pModule->package_;
    for (int i = 0; i < pModule->structs_.size(); i++) {
      ::org::labcrypto::hottentot::generator::Struct *pStruct = pModule->structs_.at(i);
      for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
        ::org::labcrypto::hottentot::generator::Declaration *declarationPtr = it->second;
        if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(declarationPtr->type_)) {
          std::string listStructName = 
            ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(declarationPtr->type_);
          GenerateSerializableStructListFile (
            pModule,
            listStructName,
            basePackageName, 
            serializableStructListTmpStr_,
            outDir_, 
            indent_
          );
        }
      }
    }
    for (int i = 0; i < pModule->services_.size(); i++) {
      pService = pModule->services_.at(i);
      std::string serviceName = pService->name_;
      ::org::labcrypto::hottentot::generator::Method *pMethod;
      for (int i = 0; i < pService->methods_.size(); i++) {
        pMethod = pService->methods_.at(i);
        std::string lowerCaseReturnType = pMethod->returnType_;
        //TODO do this for args of method and all declaration in struct
        if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string listStructName = 
            ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(pMethod->returnType_);
          GenerateSerializableStructListFile (
            pModule,
            listStructName,
            basePackageName, 
            serializableStructListTmpStr_,
            outDir_, 
            indent_
          );
        }
        ::org::labcrypto::hottentot::generator::Argument *pArg;
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pArg->type_)) {
            std::string listStructName =
              ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(pArg->type_);
            GenerateSerializableStructListFile (
              pModule,
              listStructName,
              basePackageName, 
              serializableStructListTmpStr_,
              outDir_, 
              indent_
            );
          }
        }
      }
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org