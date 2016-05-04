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
  JavaGenerator::GenerateRequestHandler (
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    ::naeem::hottentot::generator::ds::Service *pService;
    std::string basePackageName = pModule->package_;
    for (int i = 0; i < pModule->services_.size(); i++) {
      std::string basePackageName = pModule->package_;
      pService = pModule->services_.at(i);
      std::string serviceName = pService->name_;
      std::string lowerCaseServiceName = pService->name_;
      lowerCaseServiceName[0] += 32;
      std::string replacableRequestHandlerTmpStr = requestHandlerTmpStr_;
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableRequestHandlerTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace ( 
        replacableRequestHandlerTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableRequestHandlerTmpStr,
        "[%SERVICE_NAME%]", 
        pService->name_, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableRequestHandlerTmpStr,
        "[%SERVICE_NAME_LOWERCASE%]", 
        lowerCaseServiceName, 
        1
      );
      ::naeem::hottentot::generator::ds::Method *pMethod;
      std::string methodConditionStr;
      for (int i = 0; i < pService->methods_.size(); i++) {
        pMethod = pService->methods_.at(i);
        std::string lowerCaseReturnType = pMethod->returnType_;
        lowerCaseReturnType[0] += 32;
        std::string fetchedReturnTypeOfList;
        std::string lowerCaseFetchedReturnTypeOfList;
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          fetchedReturnTypeOfList = 
            ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pMethod->returnType_);
          lowerCaseFetchedReturnTypeOfList = 
            ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(fetchedReturnTypeOfList);
        }
        std::stringstream ssID;
        ssID << pMethod->GetHash();
        methodConditionStr += indent_ + indent_ +
                              "if(methodId == " + ssID.str() + "L){\n";
        methodConditionStr += indent_ + indent_ +
                              indent_ + "List <Argument> args = request.getArgs();\n";
        ::naeem::hottentot::generator::ds::Argument *pArg;
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          std::stringstream ssI;
          ssI << i;
          methodConditionStr +=
            indent_ + indent_ + indent_ + "Argument arg" + ssI.str() + 
              " = args.get(" + ssI.str() + ");\n";
          std::string argType = 
            ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pArg->type_);
          std::string capitalizedArgVar =  
            ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(pArg->variable_);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "byte[] serialized" + capitalizedArgVar;
          methodConditionStr += " = arg" + ssI.str() + ".getData();\n";

          if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pArg->type_)) {
            std::string fetchedArgTypeOfList = 
            ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pArg->type_);
            std::string upperCaseArgTypeOfList = 
              ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(fetchedArgTypeOfList);
            methodConditionStr += indent_ + indent_ + indent_ + 
                                  "Serializable" + upperCaseArgTypeOfList + "List " +
                                  "serializable" + upperCaseArgTypeOfList + "List = " +  
                                  "new Serializable" + upperCaseArgTypeOfList + "List();\n";
            methodConditionStr += indent_ + indent_ + indent_ + 
                                  "serializable" + upperCaseArgTypeOfList + "List." + 
                                  "deserialize( serialized" + capitalizedArgVar + ");\n";
            std::string argTypeOfList = 
              ::naeem::hottentot::generator::common::TypeHelper::GetJavaClassType(fetchedArgTypeOfList);                                        
            methodConditionStr += indent_ + indent_ + indent_ + 
                                  "List<" + argTypeOfList + "> " +  pArg->variable_ + " = " + 
                                  "serializable" + upperCaseArgTypeOfList + "List." +
                                  "get" + upperCaseArgTypeOfList + "List();\n"; 
          } else if (::naeem::hottentot::generator::common::TypeHelper::IsEnum(pArg->type_)) {
            methodConditionStr += indent_ + indent_ + indent_ +
                                  pArg->type_ + " " + pArg->variable_ +  " = " + 
                                  pArg->type_ + ".deserialize(serialized" +
                                  capitalizedArgVar + ");\n";
          } else if (::naeem::hottentot::generator::common::TypeHelper::IsUDT(pArg->type_)) {
            methodConditionStr += indent_ + indent_ + indent_ +
                                  pArg->type_ + " " + pArg->variable_ +
                                  " = new " + pArg->type_ + "();\n";
            methodConditionStr += indent_ + indent_ + indent_ +
                                  pArg->variable_ + ".deserialize(serialized" + 
                                  capitalizedArgVar+ ");\n";
          } else {
            std::string javaType = 
              ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pArg->type_);
            std::string capitalizedArgType = 
              ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(pArg->type_);
            std::string capitalizedArgVar = 
              ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(pArg->variable_);
            methodConditionStr += indent_ + indent_ + indent_ +
                                  javaType + " " + pArg->variable_.c_str() +
                                  " = PDTDeserializer.get" + capitalizedArgType +
                                  "(serialized" + capitalizedArgVar + ");\n";
          }
        }
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string upperCaseReturnTypeOfList = 
            ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(fetchedReturnTypeOfList);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "Serializable" + upperCaseReturnTypeOfList + "List" + " " +
                                "serializable" + upperCaseReturnTypeOfList + "List = " +
                                "new Serializable" + upperCaseReturnTypeOfList + "List();\n";
        } else if (::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ +
                                pMethod->returnType_ + " " + lowerCaseReturnType + " = null;\n"; 
        }
        methodConditionStr += indent_ + indent_ + indent_ + "Response response = new Response();\n";
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string returnTypeOfList = 
            ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(fetchedReturnTypeOfList);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "List<" + returnTypeOfList + ">" + " " +   
                                lowerCaseFetchedReturnTypeOfList + "List = " + 
                                lowerCaseServiceName +
                                "Impl." + pMethod->name_ + "(";
        } else if (::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ +
                              lowerCaseReturnType + " = " + lowerCaseServiceName +
                              "Impl." + pMethod->name_ + "(";
        } else if (::naeem::hottentot::generator::common::TypeHelper::IsVoid(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ +
                                lowerCaseServiceName +
                                "Impl." + pMethod->name_ + "(";
        } else {
          std::string javaReturnType = 
            ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pMethod->returnType_);
          methodConditionStr += indent_ + indent_ + indent_ +
                                javaReturnType +
                                " result = " +
                                lowerCaseServiceName +
                                "Impl." + pMethod->name_ + "(";
        }
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          if (i < pMethod->arguments_.size() - 1) {
            methodConditionStr += pArg->variable_ + ",";
          } else {
            methodConditionStr += pArg->variable_;
          }
        }
        methodConditionStr += ");\n";
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string upperCaseReturnTypeOfList = 
            ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(fetchedReturnTypeOfList);
          methodConditionStr += indent_ + indent_ + indent_ + 
                              "byte[] serialized" + upperCaseReturnTypeOfList + "List;\n";
          methodConditionStr += indent_ + indent_ + indent_ + 
                              "if(" + lowerCaseFetchedReturnTypeOfList + "List == null){\n";
          methodConditionStr += indent_ + indent_ + indent_ + indent_ +
                                "serialized" + upperCaseReturnTypeOfList + "List  = new byte[0];\n";
          methodConditionStr += indent_ + indent_ + indent_ + "}else{\n";
          methodConditionStr += indent_ + indent_ + indent_ + indent_ +
                                "serializable" + upperCaseReturnTypeOfList + "List." + 
                                "set" + upperCaseReturnTypeOfList + "List(" + 
                                lowerCaseFetchedReturnTypeOfList + "List);\n";
          methodConditionStr += indent_ + indent_ + indent_ + indent_ +
                                "serialized" + upperCaseReturnTypeOfList + "List = " +
                                "serializable" + upperCaseReturnTypeOfList + "List.serialize();\n"; 
          methodConditionStr += indent_ + indent_ + indent_ + "}\n";

        } else if (::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ + 
                              "byte[] serialized" + pMethod->returnType_ + ";\n";
          methodConditionStr += indent_ + indent_ + indent_ + 
                              "if(" + lowerCaseReturnType + " == null){\n";
          methodConditionStr += indent_ + indent_ + indent_ + indent_ +
                                "serialized" + pMethod->returnType_ + "  = new byte[0];\n";
          methodConditionStr += indent_ + indent_ + indent_ + "}else{\n";
          methodConditionStr += indent_ + indent_ + indent_ + "serialized" + pMethod->returnType_ + " = " +
          lowerCaseReturnType + ".serialize();\n"; 
          methodConditionStr += indent_ + indent_ + indent_ + "}\n";   
        } else if (!::naeem::hottentot::generator::common::TypeHelper::IsVoid(pMethod->returnType_)) {
          std::string javaReturnType = 
            ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pMethod->returnType_);
          std::string capitalizedReturnType = 
            ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(pMethod->returnType_);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "byte[] serializedResult = PDTSerializer.get" + capitalizedReturnType + 
                                "( result );\n";
        }
        methodConditionStr += indent_ + indent_ + indent_ + "response.setStatusCode((byte) 0);\n";
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string upperCaseReturnTypeOfList = 
            ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(fetchedReturnTypeOfList);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "response.setData(serialized" + upperCaseReturnTypeOfList +
                                "List);\n";
          methodConditionStr += indent_ + indent_ + indent_ +
                                "response.setLength(serialized" + 
                                upperCaseReturnTypeOfList + "List.length + 1);\n";  
        } else if(::naeem::hottentot::generator::common::TypeHelper::IsVoid(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ + 
                                "response.setData(new byte[]{0});\n";
          methodConditionStr += indent_ + indent_ + indent_ + 
                                "response.setLength(0);\n";
        } else if (::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ +
                                "response.setData(serialized" + pMethod->returnType_ + ");\n";
          methodConditionStr += indent_ + indent_ + indent_ +
                                "response.setLength(serialized" + 
                                pMethod->returnType_ + ".length + 1);\n";    
        } else {
          methodConditionStr +=
            indent_ + indent_ + indent_ +
              "response.setData(serializedResult);\n";
          methodConditionStr += indent_ + indent_ + indent_ +
                                "response.setLength(serializedResult.length + 1);\n";
        }
        methodConditionStr += indent_ + indent_ + indent_ + "return response;\n";
        methodConditionStr += indent_ + indent_ + "}\n";
      }
      replacableRequestHandlerTmpStr.replace (
        replacableRequestHandlerTmpStr.find("[%METHOD_CONDITIONS%]"), 
        21, 
        methodConditionStr
      );
      std::string path = outDir_ + "/" + pService->name_.c_str() + "RequestHandler.java";
      ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableRequestHandlerTmpStr);
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org