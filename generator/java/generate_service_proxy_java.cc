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
  JavaGenerator::GenerateServiceProxy (
    ::org::labcrypto::hottentot::generator::Module *pModule
  ) {

    int serializableListCounter;
    ::org::labcrypto::hottentot::generator::Service *pService;
    std::string basePackageName = pModule->package_;
    for (int i = 0; i < pModule->services_.size(); i++) {
      std::string replacableServiceProxyStrTmp = serviceProxyTmpStr_;
      pService = pModule->services_.at(i);
      pService = pModule->services_.at(i);
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableServiceProxyStrTmp, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableServiceProxyStrTmp,
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName + (extendModule_.size() > 0 ? "." : "") + extendModule_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace ( 
        replacableServiceProxyStrTmp,
        "[%SERVICE_NAME%]", 
        pService->name_, 
        1
      );
      ::org::labcrypto::hottentot::generator::Method *pMethod;
      std::string methodsStr;
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
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          methodsStr += indent_ + indent_ + "//serialize " + pArg->variable_ + "\n";
          std::string capitalalizedArgVar = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pArg->variable_);     
          if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pArg->type_)) {
            std::string fetchedArgTypeOfList;
            serializableListCounter++;
            std::stringstream serializableListCounterStream;
            serializableListCounterStream << serializableListCounter;
            fetchedArgTypeOfList = 
              ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(pArg->type_);
            std::string upperCaseArgTypeOfList = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(fetchedArgTypeOfList);
            methodsStr += indent_ + indent_ + 
                          "Serializable" + upperCaseArgTypeOfList + "List " + 
                          "serializable" + upperCaseArgTypeOfList + "List_" + 
                          serializableListCounterStream.str() + 
                          " = new Serializable" + upperCaseArgTypeOfList + "List();\n";
            methodsStr += "serializable" + upperCaseArgTypeOfList + "List_" + 
            serializableListCounterStream.str() + 
            ".set" +
            upperCaseArgTypeOfList + "List(" + pArg->variable_ + ");\n";
            methodsStr += "byte[] serialized" +  capitalalizedArgVar + 
                          " = serializable" + upperCaseArgTypeOfList + "List_" + 
                          serializableListCounterStream.str() +
                          ".serialize();\n";
          } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(pArg->type_)) {
            methodsStr += indent_ + indent_ +
                          "byte[] serialized" +
                          capitalalizedArgVar + " = " +
                          pArg->variable_ + ".serialize();\n";  
          } else {
            std::string pdtWrapperClass = 
              ::org::labcrypto::hottentot::generator::TypeHelper::GetPdtWrapperClassName(pArg->type_);
            methodsStr += indent_ + indent_ + 
                          pdtWrapperClass + " " + pArg->variable_ + "Wrapper = new " + 
                          pdtWrapperClass + "(" + pArg->variable_ + ");\n";
            methodsStr += indent_ + indent_ + 
                          "byte[] serialized" +
                          capitalalizedArgVar + " = " + 
                          pArg->variable_ + "Wrapper.serialize();\n"; 
          }
        }
        methodsStr += "\n";
        methodsStr += indent_ + indent_ + "//make request\n";
        methodsStr += indent_ + indent_ + "Request request = new Request();\n";
        std::stringstream serviceId;
        serviceId << pService->GetHash();
        methodsStr += indent_ + indent_ + "request.setServiceId(" + serviceId.str() + "L);\n";
        std::stringstream methodId;
        methodId << pMethod->GetHash();
        methodsStr += indent_ + indent_ + "request.setMethodId(" + methodId.str() + "L);\n";
        std::stringstream argSize;
        argSize << pMethod->arguments_.size();
        methodsStr +=
        indent_ + indent_ + "request.setArgumentCount((byte) " + argSize.str() + ");\n";
        methodsStr += indent_ + indent_ + "request.setType(Request.RequestType.";
        if (pService->serviceType_ == 0) {
          methodsStr += "InvokeStateless";
        } else if (pService->serviceType_ == 1) {
          methodsStr += "InvokeStatefull";
        }
        methodsStr += ");\n";
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          std::stringstream ssI;
          pArg = pMethod->arguments_.at(i);
          ssI << i;
          std::string capitalizedArgVar = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pArg->variable_);
          methodsStr += indent_ + indent_ + "Argument arg" + ssI.str() + " = new Argument();\n";
          methodsStr += indent_ + indent_ + "arg" + ssI.str() + ".setDataLength(" +
                        "serialized" + capitalizedArgVar + ".length);\n";
          methodsStr += indent_ + indent_ + 
                        "arg" + ssI.str() + ".setData(serialized" + capitalizedArgVar + ");\n";
          methodsStr += indent_ + indent_ +
                       "request.addArgument(arg" + ssI.str() + ");\n";
        }
        methodsStr += indent_ + indent_ + "int dataLength = 0;\n";
        methodsStr += indent_ + indent_ + "//calculate data length for every argument\n";
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          std::string argDataLengthVarName = pArg->variable_ + "DataLength";
          std::string capitalizedArgVar = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(pArg->variable_); 
          std::string argDataLengthByteArrayLengthVarName =
          pArg->variable_ + "DataLengthByteArrayLength";
          methodsStr += indent_ + indent_ + "// calulate " + argDataLengthVarName + "\n";
          methodsStr += indent_ + indent_ + "int " + argDataLengthVarName + "= serialized" +
          capitalizedArgVar  + ".length;\n";
          methodsStr += indent_ + indent_ + "int " + argDataLengthByteArrayLengthVarName + " = 1;\n";
          methodsStr += indent_ + indent_ + "if (" + argDataLengthVarName + " >= 0x80) {\n";
          methodsStr += indent_ + indent_ + indent_ + "if (" + argDataLengthVarName + " <= 0xff) {\n";
          methodsStr += indent_ + indent_ + indent_ + indent_ + "//ex 0x81 0xff\n";
          methodsStr += indent_ + indent_ + indent_ + indent_ + "" +
          argDataLengthByteArrayLengthVarName + " = 2;\n";
          methodsStr += indent_ + indent_ + indent_ + "} else if (" + argDataLengthVarName + " <= 0xffff) {\n";
          methodsStr += indent_ + indent_ + indent_ + indent_ + "//ex 0x82 0xff 0xff\n";
          methodsStr += indent_ + indent_ + indent_ + indent_ + "" +
          argDataLengthByteArrayLengthVarName + " = 3;\n";
          methodsStr += indent_ + indent_ + indent_ + "} else if (" + argDataLengthVarName + " <= 0xffffff) {\n";
          methodsStr += indent_ + indent_ + indent_ + indent_ + "//ex 0x83 0xff 0xff 0xff\n";
          methodsStr += indent_ + indent_ + indent_ + indent_ + "" +
          argDataLengthByteArrayLengthVarName + " = 4;\n";
          methodsStr += indent_ + indent_ + indent_ + "}\n";
          methodsStr += indent_ + indent_ + "}\n";
          methodsStr += indent_ + indent_ + "dataLength += " + argDataLengthVarName + " + " +
          argDataLengthByteArrayLengthVarName + ";\n";
        }
        methodsStr += indent_ + indent_ + "// arg count(1) + request type(1) + method ID(4) + service ID(4) = 10;\n";
        methodsStr += indent_ + indent_ + "request.setLength(10 + dataLength);\n";
        methodsStr += indent_ + indent_ + "// connect to server\n";
        methodsStr += indent_ + indent_ + "TcpClient tcpClient = TcpClientFactory.create();\n";
        methodsStr += indent_ + indent_ + "try{\n";
        methodsStr += indent_ + indent_ + indent_ + "tcpClient.connect(host, port);\n";
        methodsStr += indent_ + indent_ + "} catch (TcpClientConnectException e) {\n";
        methodsStr += indent_ + indent_ + indent_ + "throw new HottentotRuntimeException(e);\n";
        methodsStr += indent_ + indent_ + "}\n";
        methodsStr += indent_ + indent_ + "// serialize request according to HTNP\n";
        methodsStr += indent_ + indent_ + "Protocol protocol = ProtocolFactory.create();\n";
        methodsStr += indent_ + indent_ +
        "byte[] serializedRequest = protocol.serializeRequest(request);\n";
        methodsStr += indent_ + indent_ + "// send request\n";
        methodsStr += indent_ + indent_ + "try {\n";
        methodsStr += indent_ + indent_ + indent_ + "tcpClient.write(serializedRequest);\n";
        methodsStr += indent_ + indent_ + "} catch (TcpClientWriteException e) {\n";
        methodsStr += indent_ + indent_ + indent_ + "throw new HottentotRuntimeException(e);\n";
        methodsStr += indent_ + indent_ + "}\n";
        if (!::org::labcrypto::hottentot::generator::TypeHelper::IsVoid(pMethod->returnType_)) {
          methodsStr += indent_ + indent_ + "// read response from server\n";
          methodsStr += indent_ + indent_ + "byte[] buffer = new byte[256];\n";
          methodsStr += indent_ + indent_ + "while (!protocol.isResponseComplete()) {\n";
          methodsStr += indent_ + indent_ + indent_ + "byte[] dataChunkRead;\n";
          methodsStr += indent_ + indent_ + indent_ + "try {\n";
          methodsStr += indent_ + indent_ + indent_ + indent_ + "dataChunkRead = tcpClient.read();\n";
          methodsStr += indent_ + indent_ + indent_ + "} catch (TcpClientReadException e) {\n";
          methodsStr +=
            indent_ + indent_ + indent_ + indent_ + "throw new HottentotRuntimeException(e);\n";
          methodsStr += indent_ + indent_ + indent_ + "}\n";
          methodsStr +=
            indent_ + indent_ + indent_ + "protocol.processDataForResponse(dataChunkRead);\n";
          methodsStr += indent_ + indent_ + "}\n";
          methodsStr += indent_ + indent_ + "Response response = protocol.getResponse();\n";
          methodsStr += indent_ + indent_ + "// close everything\n";
          methodsStr += indent_ + indent_ + " try { \n";
          methodsStr += indent_ + indent_ + indent_ + " tcpClient.close(); \n";
          methodsStr += indent_ + indent_ + "} catch (TcpClientCloseException e) { \n";
          methodsStr += indent_ + indent_ + indent_ + "e.printStackTrace(); \n";
          methodsStr += indent_ + indent_ + "} \n";
          methodsStr += indent_ + indent_ + "//deserialize " + pMethod->returnType_ + "part from response\n";
          if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(pMethod->returnType_)) {
            std::string upperCaseReturnTypeOfList = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(fetchedReturnTypeOfList);
            serializableListCounter++;
            std::stringstream serializableListCounterStream;
            serializableListCounterStream << serializableListCounter;
            methodsStr += indent_ + indent_ +
                          "Serializable" + upperCaseReturnTypeOfList + "List" + 
                          " serializable" + upperCaseReturnTypeOfList + "List_" + 
                          serializableListCounterStream.str() +
                          " = null;\n"; 
            methodsStr += indent_ + indent_ + "if (response.getStatusCode() == -1) {\n";
            methodsStr += indent_ + indent_ + indent_ +
                          "throw new MethodNotSupportRuntimeException();\n";
            methodsStr += indent_ + indent_ + "}\n";
            methodsStr += indent_ + indent_ + 
                          "serializable" + upperCaseReturnTypeOfList + "List_" +
                          serializableListCounterStream.str() + 
                          " = new Serializable" + upperCaseReturnTypeOfList + "List();\n";
            methodsStr += indent_ + indent_ + 
                          "serializable" + upperCaseReturnTypeOfList + "List_" + 
                          serializableListCounterStream.str() + 
                          ".deserialize(response.getData());\n";
            methodsStr += indent_ + indent_ +
                          "return serializable" + upperCaseReturnTypeOfList + 
                          "List_" + 
                          serializableListCounterStream.str() + 
                          ".get" + upperCaseReturnTypeOfList + "List();\n"; 
          } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsEnum(pMethod->returnType_)) {
            methodsStr += indent_ + indent_ + "if (response.getStatusCode() == -1) {\n";
            methodsStr += indent_ + indent_ + indent_ +
                          "throw new MethodNotSupportRuntimeException();\n";
            methodsStr += indent_ + indent_ + "}\n";
            methodsStr += indent_ + indent_ +
                          "return " + pMethod->returnType_ + ".deserialize(response.getData());\n";
          } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsUDT(pMethod->returnType_)) {
            methodsStr += indent_ + indent_ +
                          returnType + " " + lowerCaseReturnType + "= null;\n"; 
            methodsStr += indent_ + indent_ + "if (response.getStatusCode() == -1) {\n";
            methodsStr += indent_ + indent_ + indent_ +
                          "throw new MethodNotSupportRuntimeException();\n";            methodsStr += indent_ + indent_ + "}\n";
            methodsStr += indent_ + indent_ + "" + lowerCaseReturnType + "= new " +
                          pMethod->returnType_ + "();\n";
            methodsStr += indent_ + indent_ + "" + lowerCaseReturnType +
                          ".deserialize(response.getData());\n";
            methodsStr += indent_ + indent_ + "return " + lowerCaseReturnType + ";\n";
          } else {
            methodsStr += indent_ + indent_ + "if (response.getStatusCode() == -1) {\n";
            methodsStr += indent_ + indent_ + indent_ +
                          "throw new MethodNotSupportRuntimeException();\n";
            methodsStr += indent_ + indent_ + "}\n";
            std::string pdtWrapperClassName = 
              ::org::labcrypto::hottentot::generator::TypeHelper::GetPdtWrapperClassName (pMethod->returnType_);
            methodsStr += indent_ + indent_ + 
                          pdtWrapperClassName + " ret = new " +
                          pdtWrapperClassName + "();\n";
            methodsStr += indent_ + indent_ +
                          "ret.deserialize(response.getData());\n";
            methodsStr += indent_ + indent_ +
                          "return ret.getValue();\n";
          }
        }
        methodsStr += indent_ + "}\n";
      }
      replacableServiceProxyStrTmp.replace (
        replacableServiceProxyStrTmp.find("[%METHODS%]"), 
        11,
        methodsStr
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
      std::string path = outDir_ + "/" + packages + "/" + 
        pService->name_.c_str() + "ServiceProxy.java";
      ::org::labcrypto::hottentot::generator::Os::WriteFile(path , replacableServiceProxyStrTmp);
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org