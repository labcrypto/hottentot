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
    ::org::labcrypto::hottentot::generator::Module *pModule
  ) {

    int serializableListCounter = 0;
    ::org::labcrypto::hottentot::generator::Service *pService;
    std::string basePackageName = pModule->package_;
    for (uint32_t i = 0; i < pModule->services_.size(); i++) {
      std::string basePackageName = pModule->package_;
      pService = pModule->services_.at(i);
      std::string serviceName = pService->name_;
      std::string lowerCaseServiceName = pService->name_;
      lowerCaseServiceName[0] += 32;
      std::string replacableRequestHandlerTmpStr = requestHandlerTmpStr_;
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableRequestHandlerTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace ( 
        replacableRequestHandlerTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName + (extendModule_.size() > 0 ? "." : "") + extendModule_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableRequestHandlerTmpStr,
        "[%SERVICE_NAME%]", 
        pService->name_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableRequestHandlerTmpStr,
        "[%SERVICE_NAME_LOWERCASE%]", 
        lowerCaseServiceName, 
        1
      );
      ::org::labcrypto::hottentot::generator::Method *pMethod;
      std::string methodConditionStr;
      for (uint32_t i = 0; i < pService->methods_.size(); i++) {
        pMethod = pService->methods_.at(i);
        std::string lowerCaseReturnType = pMethod->returnType_;
        lowerCaseReturnType[0] += 32;
        std::string fetchedReturnTypeOfList;
        std::string lowerCaseFetchedReturnTypeOfList;
        if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pMethod->returnType_)) {
          fetchedReturnTypeOfList = 
            ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(pMethod->returnType_);
          lowerCaseFetchedReturnTypeOfList = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeLowerCase(fetchedReturnTypeOfList);
        }
        std::stringstream ssID;
        ssID << pMethod->GetHash();
        methodConditionStr += indent_ + indent_ +
                              "if(methodId == " + ssID.str() + "L){\n";
        methodConditionStr += indent_ + indent_ +
                              indent_ + "List <Argument> args = request.getArgs();\n";
        ::org::labcrypto::hottentot::generator::Argument *pArg;
        for (uint32_t i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          std::stringstream ssI;
          ssI << i;
          methodConditionStr +=
            indent_ + indent_ + indent_ + "Argument arg" + ssI.str() + 
              " = args.get(" + ssI.str() + ");\n";
          std::string argType = 
            ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(pArg->type_);
          std::string capitalizedArgVar =  
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pArg->variable_);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "byte[] serialized" + capitalizedArgVar;
          methodConditionStr += " = arg" + ssI.str() + ".getData();\n";

          if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pArg->type_)) {
            std::string fetchedArgTypeOfList = 
            ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(pArg->type_);
            std::string upperCaseArgTypeOfList = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(fetchedArgTypeOfList);
            
            serializableListCounter++;
            std::stringstream serializableListCounterStream;
            serializableListCounterStream << serializableListCounter;
            methodConditionStr += indent_ + indent_ + indent_ + 
                                  "Serializable" + upperCaseArgTypeOfList + "List " +
                                  "serializable" + upperCaseArgTypeOfList + "List_" + 
                                  serializableListCounterStream.str() +
                                  " = new Serializable" + upperCaseArgTypeOfList + "List();\n";
            methodConditionStr += indent_ + indent_ + indent_ + 
                                  "serializable" + upperCaseArgTypeOfList + "List_" + 
                                  serializableListCounterStream.str() +
                                  ".deserialize( serialized" + capitalizedArgVar + ");\n";
            std::string argTypeOfList = 
              ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaClassType(fetchedArgTypeOfList);                                        
            methodConditionStr += indent_ + indent_ + indent_ + 
                                  "List<" + argTypeOfList + "> " +  pArg->variable_ + " = " + 
                                  "serializable" + upperCaseArgTypeOfList + "List_"+ 
                                  serializableListCounterStream.str() + 
                                  ".get" + upperCaseArgTypeOfList + "List();\n"; 
          } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsEnum(pArg->type_)) {
            methodConditionStr += indent_ + indent_ + indent_ +
                                  pArg->type_ + " " + pArg->variable_ +  " = " + 
                                  pArg->type_ + ".deserialize(serialized" +
                                  capitalizedArgVar + ");\n";
          } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(pArg->type_)) {
            methodConditionStr += indent_ + indent_ + indent_ +
                                  pArg->type_ + " " + pArg->variable_ +
                                  " = new " + pArg->type_ + "();\n";
            methodConditionStr += indent_ + indent_ + indent_ +
                                  pArg->variable_ + ".deserialize(serialized" + 
                                  capitalizedArgVar+ ");\n";
          } else {
            std::string javaType = 
              ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(pArg->type_);
            std::string capitalizedArgType = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pArg->type_);
            std::string capitalizedArgVar = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pArg->variable_);
            methodConditionStr += indent_ + indent_ + indent_ +
                                  javaType + " " + pArg->variable_.c_str() +
                                  " = PDTDeserializer.get" + capitalizedArgType +
                                  "(serialized" + capitalizedArgVar + ");\n";
          }
        }
        
        if (
          ::org::labcrypto::hottentot::generator::TypeHelper::IsListType
          (pMethod->returnType_)) 
        {
          serializableListCounter++;
          std::stringstream serializableListCounterStream;
          serializableListCounterStream << serializableListCounter;
          std::string upperCaseReturnTypeOfList = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital
            (fetchedReturnTypeOfList);        
          methodConditionStr += indent_ + indent_ + indent_ +
                                "Serializable" + upperCaseReturnTypeOfList + "List" + " " +
                                "serializable" + upperCaseReturnTypeOfList + "List_" + 
                                serializableListCounterStream.str() +    
                                "= new Serializable" + upperCaseReturnTypeOfList + "List();\n";
        } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ +
                                pMethod->returnType_ + " " + lowerCaseReturnType + " = null;\n"; 
        }
        methodConditionStr += indent_ + indent_ + indent_ + "Response response = new Response();\n";
        if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pMethod->returnType_)) {
          std::stringstream serializableListCounterStream;
          serializableListCounterStream << serializableListCounter;
          std::string returnTypeOfList = 
            ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(fetchedReturnTypeOfList);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "List<" + returnTypeOfList + ">" + " " +   
                                lowerCaseFetchedReturnTypeOfList + "List = " + 
                                lowerCaseServiceName +
                                "Impl." + pMethod->name_ + "(";
        } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ +
                              lowerCaseReturnType + " = " + lowerCaseServiceName +
                              "Impl." + pMethod->name_ + "(";
        } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsVoid(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ +
                                lowerCaseServiceName +
                                "Impl." + pMethod->name_ + "(";
        } else {
          std::string javaReturnType = 
            ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(pMethod->returnType_);
          methodConditionStr += indent_ + indent_ + indent_ +
                                javaReturnType +
                                " result = " +
                                lowerCaseServiceName +
                                "Impl." + pMethod->name_ + "(";
        }
        for (uint32_t i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          if (i < pMethod->arguments_.size() - 1) {
            methodConditionStr += pArg->variable_ + ",";
          } else {
            methodConditionStr += pArg->variable_;
          }
        }
        methodConditionStr += ");\n";
        if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pMethod->returnType_)) {
          std::stringstream serializableListCounterStream;
          serializableListCounterStream << serializableListCounter;
          std::string upperCaseReturnTypeOfList = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(fetchedReturnTypeOfList);
          methodConditionStr += indent_ + indent_ + indent_ + 
                              "byte[] serialized" + upperCaseReturnTypeOfList + "List;\n";
          methodConditionStr += indent_ + indent_ + indent_ + 
                              "if(" + lowerCaseFetchedReturnTypeOfList + "List == null){\n";
          methodConditionStr += indent_ + indent_ + indent_ + indent_ +
                                "serialized" + upperCaseReturnTypeOfList + "List  = new byte[0];\n";
          methodConditionStr += indent_ + indent_ + indent_ + "}else{\n";
          methodConditionStr += indent_ + indent_ + indent_ + indent_ +
                                "serializable" + upperCaseReturnTypeOfList + "List_" + 
                                serializableListCounterStream.str() + 
                                ".set" + upperCaseReturnTypeOfList + "List(" + 
                                lowerCaseFetchedReturnTypeOfList + "List);\n";
          methodConditionStr += indent_ + indent_ + indent_ + indent_ +
                                "serialized" + upperCaseReturnTypeOfList + "List = " +
                                "serializable" + upperCaseReturnTypeOfList + "List_" + 
                                serializableListCounterStream.str() + 
                                ".serialize();\n"; 
          methodConditionStr += indent_ + indent_ + indent_ + "}\n";

        } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(pMethod->returnType_)) {
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
        } else if (!::org::labcrypto::hottentot::generator::TypeHelper::IsVoid(pMethod->returnType_)) {
          std::string javaReturnType = 
            ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(pMethod->returnType_);
          std::string capitalizedReturnType = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pMethod->returnType_);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "byte[] serializedResult = PDTSerializer.get" + capitalizedReturnType + 
                                "( result );\n";
        }
        methodConditionStr += indent_ + indent_ + indent_ + "response.setStatusCode((byte) 0);\n";
        if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string upperCaseReturnTypeOfList = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(fetchedReturnTypeOfList);
          methodConditionStr += indent_ + indent_ + indent_ +
                                "response.setData(serialized" + upperCaseReturnTypeOfList +
                                "List);\n";
          methodConditionStr += indent_ + indent_ + indent_ +
                                "response.setLength(serialized" + 
                                upperCaseReturnTypeOfList + "List.length + 1);\n";  
        } else if(::org::labcrypto::hottentot::generator::TypeHelper::IsVoid(pMethod->returnType_)) {
          methodConditionStr += indent_ + indent_ + indent_ + 
                                "response.setData(new byte[]{0});\n";
          methodConditionStr += indent_ + indent_ + indent_ + 
                                "response.setLength(0);\n";
        } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(pMethod->returnType_)) {
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
      std::string packages =
        ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
          ::org::labcrypto::hottentot::generator::StringHelper::Split (
           pModule->GetPackage() + (extendModule_.size() > 0 ? "." : "") + extendModule_, 
            '.'
          ), 
          "/"
        );
      ::org::labcrypto::hottentot::generator::Os::MakeDir(outDir_ + "/" + packages);
      std::string path = outDir_ + "/" + packages + "/" + pService->name_.c_str() + "RequestHandler.java";
      ::org::labcrypto::hottentot::generator::Os::WriteFile(path , replacableRequestHandlerTmpStr);
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org