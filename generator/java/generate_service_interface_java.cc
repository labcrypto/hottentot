#include <sys/stat.h>

#include <sstream>

#include "java_generator.h"

#include "../hot.h"
#include "../string_helper.h"
#include "../os.h" 
#include "../type_helper.h" 


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  void
  JavaGenerator::GenerateServiceInterface (
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    ::naeem::hottentot::generator::ds::Service *pService;
    for (int i = 0; i < pModule->services_.size(); i++) {
      std::string basePackageName = pModule->package_;
      pService = pModule->services_.at(i);
      std::string replacableServiceTmpStr = serviceTmpStr_;
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServiceTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServiceTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServiceTmpStr, 
        "[%SERVICE_NAME%]", 
        pService->name_, 
        1
      );
      std::string serviceMethodsStr;
      ::naeem::hottentot::generator::ds::Method *pMethod;
      for (int i = 0; i < pService->methods_.size(); i++) {
        pMethod = pService->methods_.at(i);
        std::string fetchedReturnTypeOfList;
        std::string lowerCaseFetchedReturnTypeOfList;
        std::string returnType = 
          ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pMethod->returnType_);
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          fetchedReturnTypeOfList = 
            ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pMethod->returnType_);
          lowerCaseFetchedReturnTypeOfList = 
            ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(fetchedReturnTypeOfList);
          std::string returnTypeOfList = 
           ::naeem::hottentot::generator::common::TypeHelper::GetJavaClassType(fetchedReturnTypeOfList);
          returnType = "List<" + returnTypeOfList + ">";
        }
        serviceMethodsStr += indent_ + "" + returnType + " " + pMethod->name_ + "(";    
        ::naeem::hottentot::generator::ds::Argument *pArg;
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pArg->type_)) {
            std::string fetchedArgTypeOfList = 
              ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pArg->type_);
            std::string argTypeOfList = 
              ::naeem::hottentot::generator::common::TypeHelper::GetJavaClassType(fetchedArgTypeOfList);
            serviceMethodsStr += "List<" + argTypeOfList + "> " + pArg->variable_;    
          } else {
            std::string argType = 
              ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pArg->type_);
            serviceMethodsStr += argType + " " + pArg->variable_;    
          }
          if (i < pMethod->arguments_.size() - 1) {
            serviceMethodsStr += ",";
          }
        }
        serviceMethodsStr += ");\n";
      }
      replacableServiceTmpStr.replace (
        replacableServiceTmpStr.find("[%SERVICE_METHODS%]"), 
        19, 
        serviceMethodsStr
      );
      std::string path = outDir_ + "/" + pService->name_.c_str() + "Service.java";
      ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceTmpStr);
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org