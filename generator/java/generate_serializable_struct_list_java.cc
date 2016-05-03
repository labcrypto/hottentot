#include <sys/stat.h>

#include <sstream>

#include "java_generator.h"

#include "../hot.h"
#include "../string_helper.h"
#include "../os.h" 
#include "../type_helper.h" 


void 
GenerateSerializableStructListFile (
  std::string listStructName ,
  std::string basePackageName ,
  std::string replacableSerializableStructListTmpStr ,
  std::string outDir ,
  std::string indent
) {
  std::string lowerCaseStructName = 
    ::naeem::hottentot::generator::common::StringHelper::MakeFirstLowerCase(listStructName);
  std::string upperCaseStructName = 
    ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(listStructName);
  std::string serializableHottentotTypeName = 
    ::naeem::hottentot::generator::common::TypeHelper::GetSerializableHottentotType(listStructName);
  std::string lowerCaseSerializableHottentotTypeName = 
    ::naeem::hottentot::generator::common::StringHelper::MakeFirstLowerCase(serializableHottentotTypeName);
  std::string javaClassType = 
    ::naeem::hottentot::generator::common::TypeHelper::GetJavaClassType(listStructName);
  std::string instanciationHottentotTypeStr = "";
  std::string getValueMethodStr = "";
  if (!::naeem::hottentot::generator::common::TypeHelper::IsUDT(listStructName)) {
    getValueMethodStr = ".getValue()";
  }
  if (!::naeem::hottentot::generator::common::TypeHelper::IsUDT(listStructName)) {
    instanciationHottentotTypeStr = 
      serializableHottentotTypeName + " " +
      lowerCaseSerializableHottentotTypeName + " = " + 
      "new " + serializableHottentotTypeName + "( " + 
      lowerCaseStructName + 
      " );";
  }
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%BASE_PACKAGE_NAME%]",
    basePackageName,
    1
  );
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%INDENT%]", 
    indent ,
    1
  );
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%STRUCT_NAME%]",
    listStructName,
    1
  );
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%UPPER_CASE_STRUCT_NAME%]",
    upperCaseStructName,
    1
  );
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%LOWER_CASE_STRUCT_NAME%]",
    lowerCaseStructName,
    1
  );            
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%HOTTENTOT_TYPE%]",
    serializableHottentotTypeName,
    1
  );            
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%LOWER_CASE_HOTTENTOT_TYPE%]",
    lowerCaseSerializableHottentotTypeName,
    1
  );            
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%JAVA_CLASS_TYPE%]",
    javaClassType,
    1
  );            
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr,
    "[%INSTANCIATION_HOTTENTOT_TYPE%]",
    instanciationHottentotTypeStr,
    1
  );     
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr, 
    "[%GET_VALUE_METHOD%]",
    getValueMethodStr,
    1);        
  std::string path = outDir + "/Serializable" + upperCaseStructName.c_str() + "List.java";
  ::naeem::hottentot::generator::common::Os::WriteFile (
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
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    ::naeem::hottentot::generator::ds::Service *pService;
    std::string basePackageName = pModule->package_;
    for (int i = 0; i < pModule->structs_.size(); i++) {
      ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(i);
      for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
        ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(declarationPtr->type_)) {
          std::string listStructName = 
            ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(declarationPtr->type_);
          GnerateSerializableStructListFile (
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
      ::naeem::hottentot::generator::ds::Method *pMethod;
      for (int i = 0; i < pService->methods_.size(); i++) {
        pMethod = pService->methods_.at(i);
        std::string lowerCaseReturnType = pMethod->returnType_;
        //TODO do this for args of method and all declaration in struct
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string listStructName = 
            ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pMethod->returnType_);
          GenerateSerializableStructListFile (
            listStructName,
            basePackageName, 
            serializableStructListTmpStr_,
            outDir_, 
            indent_
          );
        }
        ::naeem::hottentot::generator::ds::Argument *pArg;
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pArg->type_)) {
            std::string listStructName =
              ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pArg->type_);
            GenerateSerializableStructListFile (
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