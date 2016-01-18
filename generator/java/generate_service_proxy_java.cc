#include <sys/stat.h>
#include <sstream>
#include "java_generator.h"
#include "../ds/hot.h"
#include "../common/string_helper.h"
#include "../common/os.h" 
#include "../common/type_helper.h" 


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
        void
        JavaGenerator::GenerateServiceProxy(::naeem::hottentot::generator::ds::Module *pModule) {
          ::naeem::hottentot::generator::ds::Service *pService;
          std::string basePackageName = pModule->package_;
          for (int i = 0; i < pModule->services_.size(); i++) {
            std::string replacableServiceProxyStrTmp = serviceProxyTmpStr_;
            pService = pModule->services_.at(i);
            pService = pModule->services_.at(i);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyStrTmp , "[%INDENT%]" , indent_ , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyStrTmp,"[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyStrTmp,"[%SERVICE_NAME%]" , pService->name_ , 1);
            //loop on service methods
            ::naeem::hottentot::generator::ds::Method *pMethod;
            std::string methodsStr;
            for (int i = 0; i < pService->methods_.size(); i++) {
              pMethod = pService->methods_.at(i);

              std::string fetchedReturnTypeOfList;
              std::string lowerCaseFetchedReturnTypeOfList;
              std::string returnType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pMethod->returnType_);
            
              std::string lowerCaseReturnType = pMethod->returnType_;
              std::string capitalizedReturnType = 
              ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
              pMethod->returnType_);
              lowerCaseReturnType[0] += 32;
              if(::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)){
                fetchedReturnTypeOfList = ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pMethod->returnType_);
                returnType = "List<" + fetchedReturnTypeOfList + ">";
              }
              methodsStr += indent_ + "public " + returnType + " " + pMethod->name_ + "(";
              ::naeem::hottentot::generator::ds::Argument *pArg;
              for (int i = 0; i < pMethod->arguments_.size(); i++) {
                pArg = pMethod->arguments_.at(i);
                std::string argType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pArg->type_);
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
              ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(pArg->variable_);     
              methodsStr += indent_ + indent_ +
              "byte[] serialized" +
              capitalalizedArgVar + " = " +
              pArg->variable_ + ".serialize();\n";
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
              methodsStr += indent_ + indent_ + "Argument arg" + ssI.str() + " = new Argument();\n";
              methodsStr += indent_ + indent_ + "arg" + ssI.str() + ".setDataLength(";              
              methodsStr += pArg->variable_ + ".serialize().length);\n";
              methodsStr += indent_ + indent_ + 
                            "arg" + ssI.str() + ".setData(" + pArg->variable_.c_str() + ".serialize());\n";
              methodsStr += indent_ + indent_ +
                           "request.addArgument(arg" + ssI.str() + ");\n";
            }
            //calculate request length
            methodsStr += indent_ + indent_ + "int dataLength = 0;\n";
            methodsStr += indent_ + indent_ + "//calculate data length for every argument\n";
            for (int i = 0; i < pMethod->arguments_.size(); i++) {
              pArg = pMethod->arguments_.at(i);
              std::string argDataLengthVarName = pArg->variable_ + "DataLength";
              std::string capitalizedArgVar = 
              ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(pArg->variable_); 
              std::string argDataLengthByteArrayLengthVarName =
              pArg->variable_ + "DataLengthByteArrayLength";
              methodsStr += indent_ + indent_ + "//calulate " + argDataLengthVarName + "\n";
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
            methodsStr += indent_ + indent_ + "//arg count + request type + method ID + service ID = 18;\n";
            methodsStr += indent_ + indent_ + "request.setLength(18 + dataLength);\n";
            methodsStr += indent_ + indent_ + "//connect to server\n";
            methodsStr += indent_ + indent_ + "TcpClient tcpClient = TcpClientFactory.create();\n";
            methodsStr += indent_ + indent_ + "try{\n";
            methodsStr += indent_ + indent_ + indent_ + "tcpClient.connect(host, port);\n";
            methodsStr += indent_ + indent_ + "} catch (TcpClientConnectException e) {\n";
            methodsStr += indent_ + indent_ + indent_ + "throw new HottentotRuntimeException(e);\n";
            methodsStr += indent_ + indent_ + "}\n";
            methodsStr += indent_ + indent_ + "//serialize request according to HTNP\n";
            methodsStr += indent_ + indent_ + "Protocol protocol = ProtocolFactory.create();\n";
            methodsStr += indent_ + indent_ +
            "byte[] serializedRequest = protocol.serializeRequest(request);\n";
            methodsStr += indent_ + indent_ + "//send request\n";
            methodsStr += indent_ + indent_ + "try {\n";
            methodsStr += indent_ + indent_ + indent_ + "tcpClient.write(serializedRequest);\n";
            methodsStr += indent_ + indent_ + "} catch (TcpClientWriteException e) {\n";
            methodsStr += indent_ + indent_ + indent_ + "throw new HottentotRuntimeException(e);\n";
            methodsStr += indent_ + indent_ + "}\n";
            methodsStr += indent_ + indent_ + "//read response from server\n";
            methodsStr += indent_ + indent_ + "byte[] buffer = new byte[256];\n";
            methodsStr += indent_ + indent_ + "while (!protocol.IsResponseComplete()) {\n";
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
            methodsStr += indent_ + indent_ + "//deserialize token part of response\n";
            methodsStr += indent_ + indent_ + "Response response = protocol.getResponse();\n";
            methodsStr += indent_ + indent_ + "//close everything\n";
            methodsStr += indent_ + indent_ + " try { \n";
            methodsStr += indent_ + indent_ + indent_ + " tcpClient.close(); \n";
            methodsStr += indent_ + indent_ + "} catch (TcpClientCloseException e) { \n";
            methodsStr += indent_ + indent_ + indent_ + "e.printStackTrace(); \n";
            methodsStr += indent_ + indent_ + "} \n";
            methodsStr += indent_ + indent_ + "//deserialize " + pMethod->returnType_ + "part from response\n";
            
            
         
            if(::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)){
              methodsStr += indent_ + indent_ +
                            "Serializable" + fetchedReturnTypeOfList + "List" + 
                            " serializable" + fetchedReturnTypeOfList + "List = null;\n"; 
              methodsStr += indent_ + indent_ + "if (response.getStatusCode() == -1) {\n";
              methodsStr += indent_ + indent_ + indent_ + "//TODO\n";
              methodsStr += indent_ + indent_ + "}\n";
              methodsStr += indent_ + indent_ + 
                            "serializable" + fetchedReturnTypeOfList + "List = " 
                            "new Serializable" + fetchedReturnTypeOfList + "List();\n";
              methodsStr += indent_ + indent_ + 
                            "serializable" + fetchedReturnTypeOfList + "List." + 
                            "deserialize(response.getData());\n";
              methodsStr += indent_ + indent_ +
                            "return serializable" + fetchedReturnTypeOfList + 
                            "List.getTokenList();\n"; 
            }else{
              methodsStr += indent_ + indent_ +
                            returnType + " " + lowerCaseReturnType + "= null;\n"; 
              methodsStr += indent_ + indent_ + "if (response.getStatusCode() == -1) {\n";
              methodsStr += indent_ + indent_ + indent_ + "//TODO\n";
              methodsStr += indent_ + indent_ + "}\n";
              methodsStr += indent_ + indent_ + "" + lowerCaseReturnType + "= new " +
                            pMethod->returnType_ + "();\n";
              methodsStr += indent_ + indent_ + "" + lowerCaseReturnType +
                            ".deserialize(response.getData());\n";
              methodsStr += indent_ + indent_ + "return " + lowerCaseReturnType + ";\n";
            }
            
            methodsStr += indent_ + "}\n";
          }
          replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%METHODS%]"), 11,
           methodsStr);
          std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxy.java";
          ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceProxyStrTmp);
        }
      }


      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM