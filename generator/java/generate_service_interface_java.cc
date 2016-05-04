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