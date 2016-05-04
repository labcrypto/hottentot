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
#include "../os.h" 
#include "../method.h" 
#include "../service.h" 
#include "../type_helper.h" 


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  void
  JavaGenerator::GenerateServerImpls (
    ::org::labcrypto::hottentot::generator::Module *pModule
  ) {
    std::string basePackageName = pModule->package_;
    ::org::labcrypto::hottentot::generator::Service *pService;
    ::org::labcrypto::hottentot::generator::Method *pMethod;
    for (int i = 0; i < pModule->services_.size(); i++) {
      std::string replacableServerImplTmpStr = serverImplTmpStr_;  
      pService = pModule->services_.at(i);
      std::string serviceName = pService->GetName();
      std::string methodsStr = "";
      for (int i = 0; i < pService->methods_.size(); i++) {
        pMethod = pService->methods_.at(i);
        std::string fetchedReturnTypeOfList;
        std::string lowerCaseFetchedReturnTypeOfList;
        std::string returnType = ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(pMethod->returnType_);
        std::string lowerCaseReturnType = pMethod->returnType_;
        std::string capitalizedReturnType = 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pMethod->returnType_);
        lowerCaseReturnType[0] += 32;
        if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pMethod->returnType_)) {
          fetchedReturnTypeOfList = 
            ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(pMethod->returnType_);
          std::string returnTypeOfList = 
            ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaClassType(fetchedReturnTypeOfList);
          returnType = "List<" + returnTypeOfList + ">";
        }
        methodsStr += indent_ + "@Override\n";
        methodsStr += indent_ + "public " + returnType + " " + pMethod->name_ + "(";
        ::org::labcrypto::hottentot::generator::Argument *pArg;
        std::string fetchedArgTypeOfList;
        std::string argType;
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pArg->type_)) {
            fetchedArgTypeOfList =
              ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(pArg->type_);  
            std::string argTypeOfList = 
              ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaClassType(fetchedArgTypeOfList);
            argType = "List<" + argTypeOfList + ">";
          } else {
            argType = ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(pArg->type_);  
          }
          methodsStr += argType + " " + pArg->variable_;
          if (i < pMethod->arguments_.size() - 1) {
            methodsStr += ",";
          }
        }
        methodsStr += ") { \n";
        if (!TypeHelper::IsVoid(returnType)) {
          if (TypeHelper::IsJavaNullable(returnType)) {
            methodsStr += indent_ + indent_ + "return null;\n";
          } else {
            methodsStr += indent_ + indent_ + "return 0;\n";
          }
        }
        methodsStr +=  indent_ + "}\n";
      }
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableServerImplTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableServerImplTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableServerImplTmpStr,
        "[%METHODS%]", 
        methodsStr, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableServerImplTmpStr,
        "[%SERVICE_NAME%]", 
        serviceName, 
        1
      );
      std::string packages =
        ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
          ::org::labcrypto::hottentot::generator::StringHelper::Split (
           pModule->GetPackage(), 
            '.'
          ), 
          "/"
        );
      ::org::labcrypto::hottentot::generator::Os::MakeDir(serverOutDir_ + "/" + packages);
      std::string path = serverOutDir_ + "/" + packages + "/" + serviceName + "Impl.java";
      ::org::labcrypto::hottentot::generator::Os::WriteFile (
        path, 
        replacableServerImplTmpStr
      );
    }          
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org