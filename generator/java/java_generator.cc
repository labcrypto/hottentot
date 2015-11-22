/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
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

#include "java_generator.h"
#include "../ds/hot.h"

namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
		void
		JavaGenerator::Generate(::naeem::hottentot::generator::ds::Hot *hot,
				        ::naeem::hottentot::generator::GenerationConfig &generationConfig) {
		  	// TODO
			//FakeInsert();

			outDir_ = generationConfig.outDir_;
		    ReadTemplateFiles();
		    outDir_ = "/home/developer/Desktop/generated";

		     ::naeem::hottentot::generator::ds::Struct *pStruct;
		     std::vector<naeem::hottentot::generator::ds::Module*> modules = hot->modules_;
		     for (int i = 0; i < modules.size(); i++) {
		         ::naeem::hottentot::generator::ds::Module *pModule = modules.at(i);
		         GenerateStructs(pModule);
		         GenerateAbstractService(pModule);
		         GenerateServiceInterface(pModule);		        
		         GenerateRequestHandler(pModule);
		         GenerateServiceProxyBuilder(pModule);
		         GenerateServiceProxy(pModule);
		     }
		    //std::cout << hot->GetModules().at(0)->GetMethod()-> << std::endl;
		    std::cout << "Java Generation done." << std::endl;
		}

		void
		JavaGenerator::ReadTemplateFiles() {
		    //using the ds to write .hot file

			    //TODO use buffer reading
//			    char buffer[100];
//			    FILE* f = fopen("/home/developer/Desktop/templates/struct.tmp","rb");
//				std::string str;
//			    while(true){
//			        unsigned int r = fread(buffer , sizeof(char), 10 ,f);
//			        str += reinterpret_cast< char const* >(buffer);
//			        if(r == 0){
//			            break;
//			        }
//			    }
//
//			    fclose(f);
//			    f = fopen("/home/developer/Desktop/templates/new.tmp","wb");
//			    fwrite(str.c_str() , sizeof(char), str.length(),f);
//			    fclose(f);

		    is.open("/home/developer/projects/hottentot-git/generator/java/templates/struct.tmp", std::ios::in);
		    //TODO use buffer reader
		    char c;
		    while ((c = is.get()) != -1) {
		        structTmpStr_ += c;
		    }
		    is.close();
		    is.open("/home/developer/projects/hottentot-git/generator/java/templates/abstractService.tmp", std::ios::in);
		    //TODO use buffer reader
		    while ((c = is.get()) != -1) {
		        abstractServiceTmpStr_ += c;
		    }
		    is.close();

		    //service interface
		    is.open("/home/developer/projects/hottentot-git/generator/java/templates/service.tmp", std::ios::in);
		    //TODO use buffer reader
		    while ((c = is.get()) != -1) {
		        serviceTmpStr_ += c;
		    }
		    is.close();
		    //service proxy
		    is.open("/home/developer/projects/hottentot-git/generator/java/templates/serviceProxy.tmp",
		            std::ios::in);
		    //TODO use buffer reader
		    while ((c = is.get()) != -1) {
		        serviceProxyTmpStr_ += c;
		    }
		    is.close();

		    //service proxy builder
		    is.open("/home/developer/projects/hottentot-git/generator/java/templates/serviceProxyBuilder.tmp",
		            std::ios::in);
		    //TODO use buffer reader
		    while ((c = is.get()) != -1) {
		        serviceProxyBuilderTmpStr_ += c;
		    }
		    is.close();

		    //request handler
		    is.open("/home/developer/projects/hottentot-git/generator/java/templates/requestHandler.tmp",
		            std::ios::in);
		    //TODO use buffer reader
		    while ((c = is.get()) != -1) {
		        requestHandlerTmpStr_ += c;
		    }
		    is.close();
//			std::cout << "---------------" << std::endl;
//			std::cout << structTmpStr_;
//			std::cout << abstractServiceTmpStr_;
//			std::cout << serviceTmpStr_;
//			std::cout << serviceProxyBuilderTmpStr_;
//			std::cout << serviceProxyTmpStr_;
//			std::cout << requestHandlerTmpStr_;
		}

		void
		JavaGenerator::GenerateStructs(::naeem::hottentot::generator::ds::Module *pModule) {
		    //loop on structs in everey module
		    //cout << structTmpStr << endl << "-----" << endl;
		     for (int i = 0; i < pModule->structs_.size(); i++) {
		         ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(i);
				 std::string path = outDir_ + "/" +  pStruct->name_.c_str() + ".java";
		         os.open(path.c_str()  , std::ios::trunc);
		         std::string basePackageName = pModule->package_;
		         std::string replacableStructTmpStr = structTmpStr_;
		         while(replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos){
		         	replacableStructTmpStr.replace(replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);	
		         }
		         while(replacableStructTmpStr.find("[%STRUCT_NAME%]") != std::string::npos){
		         	replacableStructTmpStr.replace(replacableStructTmpStr.find("[%STRUCT_NAME%]"), 15 , pStruct->name_);	
		         }
		         std::string declarationStr;
		         std::string getterSetterStr;
		         
		         for (int i = 0; i < pStruct->declarations_.size(); i++) {
		         	//TODO change string to string
		             ::naeem::hottentot::generator::ds::Declaration *declarationPtr = pStruct->declarations_.at(i);
		             if (declarationPtr->type_.compare("string") == 0){
		             	declarationPtr->type_[0] = 'S';
		             }
		             std::string declarationName = declarationPtr->variable_;
		             std::string capitalizedDeclarationName = declarationPtr->variable_;
		             capitalizedDeclarationName[0] -= 32;
		             declarationStr += "\tprivate " + declarationPtr->type_ + " " + declarationName + ";\n";
		             getterSetterStr += "\tpublic void set" + capitalizedDeclarationName + "(" + declarationPtr->type_ + " " + declarationName + ") {\n";
		             getterSetterStr += "\t\tthis." + declarationName + " = " + declarationName + ";\n";
		             getterSetterStr += "\t}\n";
		             getterSetterStr += "\tpublic " + declarationPtr->type_ + " get" + capitalizedDeclarationName + "() {\n";
		             getterSetterStr += "\t\treturn " + declarationPtr->variable_ + ";\n";
		             getterSetterStr += "\t}\n";
		         }
		         replacableStructTmpStr.replace(replacableStructTmpStr.find("[%MEMBERS%]"), 11,
		                                        declarationStr + getterSetterStr);
		         os.write(replacableStructTmpStr.c_str(), replacableStructTmpStr.size());
		         os.close();
		     }
		}

		void
		JavaGenerator::GenerateAbstractService(::naeem::hottentot::generator::ds::Module *pModule) {
		    //loop for every services
		    ::naeem::hottentot::generator::ds::Service *pService;
		    std::string replacableAbstractServiceTmpStr;
		    for (int i = 0; i < pModule->services_.size(); i++) {
		        //write abstractService.tmp
		        std::string basePackageName = pModule->package_;
		        pService = pModule->services_.at(i);
		        std::string path = outDir_ + "/Abstract" + pService->name_.c_str() + "Service.java";
		        os.open(path.c_str() , std::ios::trunc);
		        replacableAbstractServiceTmpStr = abstractServiceTmpStr_;


		        while(replacableAbstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos){
		         	replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);	
		        }
		        while(replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]") != std::string::npos){
		         	replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16 , pService->name_);	
		        }
		        std::stringstream ssID;
		        //TODO get service ID from hot parser
		        //ssID << pService->id_;
		        ssID << "1";
		        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_ID%]"), 14, ssID.str());
		        os.write(replacableAbstractServiceTmpStr.c_str(), replacableAbstractServiceTmpStr.size());
		        os.close();
		   }
		}

		void
		JavaGenerator::GenerateServiceInterface(::naeem::hottentot::generator::ds::Module *pModule) {
		    ::naeem::hottentot::generator::ds::Service *pService;
		    std::string replacableServiceTmpStr;
		    for (int i = 0; i < pModule->services_.size(); i++) {
		        //write abstractService.tmp
		        std::string basePackageName = pModule->package_;
		        pService = pModule->services_.at(i);
		        //write service interface
		        std::string replacableServiceTmpStr = serviceTmpStr_;
		        //std::cout << outDir_;
		        std::string path = outDir_ + "/" + pService->name_.c_str() + "Service.java";
		 
		        //os.open( path.c_str(), std::ios::trunc);
		        while(replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos){
		         	replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);	
		        }
		        while(replacableServiceTmpStr.find("[%SERVICE_NAME%]") != std::string::npos){
		         	replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_NAME%]"), 16 , pService->name_);	
		        }
		        std::string serviceMethodsStr;
		        //loop for service methods
		        ::naeem::hottentot::generator::ds::Method *pMethod;
		        for (int i = 0; i < pService->methods_.size(); i++) {
		            pMethod = pService->methods_.at(i);
		            serviceMethodsStr += "\t" + pMethod->returnType_ + " " + pMethod->name_ + "(";
		            //loop on methods arguments
		            ::naeem::hottentot::generator::ds::Argument *pArg;
		            for (int i = 0; i < pMethod->arguments_.size(); i++) {
		                pArg = pMethod->arguments_.at(i);
		                serviceMethodsStr +=  pArg->type_ + " " + pArg->variable_;
		                if (i < pMethod->arguments_.size() - 1) {
		                    serviceMethodsStr += ",";
		                }
		            }
		            serviceMethodsStr += ") throws TcpClientConnectException , TcpClientReadException , TcpClientWriteException;";
		        };
		        //replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_METHODS%]"), 19, serviceMethodsStr);
		        os.write(replacableServiceTmpStr.c_str(), replacableServiceTmpStr.size());
		        os.close();

		    }
		 }


		 void
		 JavaGenerator::GenerateServiceProxyBuilder(::naeem::hottentot::generator::ds::Module *pModule) {
		    ::naeem::hottentot::generator::ds::Service *pService;
		    std::string replacableServiceProxyBuilderTmpStr;
		    for (int i = 0; i < pModule->services_.size(); i++) {
		        //write abstractService.tmp
		        std::string basePackageName = pModule->package_;
		        pService = pModule->services_.at(i);
		        std::string replacableServiceProxyBuilderTmpStr;
		        //write service proxy builder
		        std::string path = outDir_ + "/" +  pService->name_.c_str() + "ServiceProxyBuilder.java";
		        os.open(path.c_str() , std::ios::trunc);
		        replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr_;
		        while(replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos){
		         	replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);	
		        }
		        while(replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]") != std::string::npos){
		         	replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16 , pService->name_);	
		        }
		        os.write(replacableServiceProxyBuilderTmpStr.c_str(), replacableServiceProxyBuilderTmpStr.size());
		        os.close();
		    }

		}

		void
		JavaGenerator::GenerateRequestHandler(::naeem::hottentot::generator::ds::Module *pModule) {
		    ::naeem::hottentot::generator::ds::Service *pService;
		    std::string replacableRequestHandlerTmpStr;
		    std::string basePackageName = pModule->package_;
		    for (int i = 0; i < pModule->services_.size(); i++) {
		        std::string basePackageName = pModule->package_;
		        pService = pModule->services_.at(i);
		        std::string path = outDir_ + "/" +  pService->name_.c_str() + "RequestHandler.java";
		        os.open(path.c_str());
		        std::string serviceName = pService->name_;
		        std::string lowerCaseServiceName = pService->name_;
		        lowerCaseServiceName[0] += 32;
		        replacableRequestHandlerTmpStr = requestHandlerTmpStr_;
		       

		        while(replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos){
		         	replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);	
		        }
		        while(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]") != std::string::npos){
		         	replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16 , pService->name_);	
		        }
		        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME_LOWERCASE%]"), 26,
		                                               lowerCaseServiceName);

		        ::naeem::hottentot::generator::ds::Method *pMethod;
		        std::string methodConditionStr;

		        for (int i = 0; i < pService->methods_.size(); i++) {
		            pMethod = pService->methods_.at(i);
		            std::string lowerCaseReturnType = pMethod->returnType_;
		            lowerCaseReturnType[0] += 32;
		            std::stringstream ssID;
		            //TODO(alisharifi) make method id by hashing
		            //ssID << pMethod->id_;
		            ssID << 1;
		            methodConditionStr += "if(methodId == " + ssID.str() + "){\n";
		            methodConditionStr += "\t\tList <Argument> args = request.getArgs();\n";
		            ::naeem::hottentot::generator::ds::Argument *pArg;
		            for (int i = 0; i < pMethod->arguments_.size(); i++) {
		                pArg = pMethod->arguments_.at(i);
		                std::stringstream ssI;
		                ssI << i;
		                methodConditionStr += "\t\tArgument arg" + ssI.str() + " = args.get(" + ssI.str() + ");\n";
		                methodConditionStr += "\t\tbyte[] serialized" + pArg->type_;
		                methodConditionStr += " = arg" + ssI.str() + ".getData();\n";
		                methodConditionStr += "\t\t" + pArg->type_ + " " + pArg->variable_ + " = new " + pArg->type_ + "();\n";
		                methodConditionStr += "\t\t" + pArg->variable_ + ".deserialize(serialized" + pArg->type_ + ");\n";
		            }
		            methodConditionStr += "\t\t" + pMethod->returnType_ + " " + lowerCaseReturnType + " = null;\n";
		            methodConditionStr += "\t\tResponse response = new Response();\n";
		            //methodConditionStr += "\t\ttry{\n";
		            methodConditionStr +=
		                    "\t\t" + lowerCaseReturnType + " = " + lowerCaseServiceName + "Impl." + pMethod->name_ + "(";
		            for (int i = 0; i < pMethod->arguments_.size(); i++) {
		                pArg = pMethod->arguments_.at(i);
		                methodConditionStr += pArg->variable_;
		                if (i < pMethod->arguments_.size() - 1) {
		                    methodConditionStr += pArg->variable_ += ",";
		                }
		            }
		            methodConditionStr += ");\n";
		            methodConditionStr +=
		                    "\t\tbyte[] serialized" + pMethod->returnType_ + " = " + lowerCaseReturnType + ".serialize();\n";
		            methodConditionStr += "\t\tresponse.setStatusCode((byte) 100);\n";
		            methodConditionStr += "\t\tresponse.setData(serialized" + pMethod->returnType_ + ");\n";
		            methodConditionStr += "\t\tresponse.setLength(serialized" + pMethod->returnType_ + ".length + 1);\n";
		            //methodConditionStr += "\t\t} catch (Exception e) {\n";
		            methodConditionStr += "\t\te.printStackTrace();\n";
		            //methodConditionStr += "\t\t}\n";
		            methodConditionStr += "\t\treturn response;\n";
		            methodConditionStr += "\t}";

		        }
		        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%METHOD_CONDITIONS%]"), 21,
		                                               methodConditionStr);
		        os.write(replacableRequestHandlerTmpStr.c_str(), replacableRequestHandlerTmpStr.size());
		        os.close();
		    }



			//sample code
			    //    if(methodId == 1) {
			    //        List <Argument> args = request.getArgs();
			    //        Argument arg0 = args.get(0);
			    //        byte[]
			    //        serializedCredential = arg0.getData();
			    //        Credential credential = new Credential();
			    //        credential.deserialize(serializedCredential);
			    //        Token token = null;
			    //        Response response = new Response();
			    //        try {
			    //            token = authenticationImpl.authenticate(credential);
			    //            byte[]
			    //            serializedToken = token.serialize();
			    //            response.setStatusCode((byte) 100);
			    //            response.setData(serializedToken);
			    //            response.setLength(serializedToken.length + 1);
			    //
			    //        } catch (Exception e) {
			    //            e.printStackTrace();
			    //        }
			    //
			    //        return response;
			    //    }
		}

		void
		JavaGenerator::GenerateServiceProxy(::naeem::hottentot::generator::ds::Module *pModule) {
		    ::naeem::hottentot::generator::ds::Service *pService;
		    std::string basePackageName = pModule->package_;
		    for (int i = 0; i < pModule->services_.size(); i++) {
		        std::string replacableServiceProxyStrTmp = serviceProxyTmpStr_;
		        pService = pModule->services_.at(i);
		        std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxy.java";
		        os.open(path.c_str() , std::ios::trunc);
		        pService = pModule->services_.at(i);
		        while(replacableServiceProxyStrTmp.find("[%BASE_PACKAGE_NAME%]") != std::string::npos){
		         	replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);	
		        }
		        while(replacableServiceProxyStrTmp.find("[%SERVICE_NAME%]") != std::string::npos){
		         	replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%SERVICE_NAME%]"), 16 , pService->name_);	
		        }

		        //loop on service methods
		        ::naeem::hottentot::generator::ds::Method *pMethod;
		        std::string methodsStr;
		        for (int i = 0; i < pService->methods_.size(); i++) {
		            pMethod =  pService->methods_.at(i);
		            pMethod = pService->methods_.at(i);
		            methodsStr += "public " + pMethod->returnType_ + " " + pMethod->name_ + "(";
		            ::naeem::hottentot::generator::ds::Argument *pArg;
		            for (int i = 0; i < pMethod->arguments_.size(); i++) {

		                pArg = pMethod->arguments_.at(i);
		                methodsStr += pArg->type_ + " " + pArg->variable_;
		                if (i < pMethod->arguments_.size() - 1) {
		                    methodsStr += ",";
		                }
		            }
		            methodsStr += ") throws Exception { \n";
		            for (int i = 0; i < pMethod->arguments_.size(); i++) {
		                methodsStr += "\t\t//serialize " + pArg->variable_ + "\n";
		                methodsStr += "\t\tbyte[] serialized" + pArg->type_ + " = " + pArg->variable_ + ".serialize();\n";
		            }
		            methodsStr += "\n";
		            methodsStr += "\t\t//make request\n";
		            methodsStr += "\t\tRequest request = new Request();\n";
		            std::stringstream serviceId;
		            //TODO(alisharifi) make service id by hashing
		            //serviceId << pService->id_;
		            serviceId << "1";
		            methodsStr += "\t\trequest.setServiceId((byte) " + serviceId.str() + ");\n";
		            std::stringstream methodId;
		            //TODO(alisharifi) make method id by hashing
		            //methodId << pMethod->id_;
		            methodId << "1";
		            methodsStr += "\t\trequest.setMethodId((byte) " + methodId.str() + ");\n";
		            std::stringstream argSize;
		            argSize << pMethod->arguments_.size();
		            methodsStr += "\t\trequest.setArgumentCount((byte) " + argSize.str() + ");\n";
		            methodsStr += "\t\trequest.setType(Request.RequestType.";
		            
		            //std::cout << pService->serviceType_;
		            if(pService->serviceType_ == 0) {
		                methodsStr += "InvokeStateless";
		            }else if(pService->serviceType_ == 1){
		                methodsStr += "InvokeStatefull";
		            }
		            methodsStr += ");\n";
		            for (int i = 0; i < pMethod->arguments_.size(); i++) {
		                std::stringstream ssI;
		                pArg = pMethod->arguments_.at(i);
		                ssI << i;
		                methodsStr += "\t\tArgument arg" + ssI.str() + " = new Argument();\n";
		                methodsStr += "\t\targ" + ssI.str() + ".setDataLength(" + pArg->variable_.c_str() + ".serialize().length);\n";
		                methodsStr += "\t\targ" + ssI.str() + ".setData(" + pArg->variable_.c_str() + ".serialize());\n";
		                methodsStr += "\t\trequest.addArgument(arg" + ssI.str() + ");\n";
		            }
		            //calculate request length
		            methodsStr += "\t\tint dataLength = 0;\n";
		            methodsStr += "\t\t//calculate data length for every argument\n";
		            for(int i= 0 ; i < pMethod->arguments_.size() ; i++){
		                pArg = pMethod->arguments_.at(i);
		                std::string argDataLengthVarName =  pArg->variable_ + "DataLength";
		                std::string argDataLengthByteArrayLengthVarName =  pArg->variable_ + "DataLengthByteArrayLength";
		                methodsStr += "\t\t//calulate " + argDataLengthVarName + "\n";
		                methodsStr += "\t\tint " + argDataLengthVarName + "= serialized" + pArg->type_ + ".length;\n";
		                methodsStr += "\t\tint " + argDataLengthByteArrayLengthVarName + " = 1;\n";
		                methodsStr += "\t\tif (" + argDataLengthVarName + " >= 0x80) {\n";
		                methodsStr += "\t\t\tif (" + argDataLengthVarName + " <= 0xff) {\n";
		                methodsStr += "\t\t\t\t//ex 0x81 0xff\n";
		                methodsStr += "\t\t\t\t" + argDataLengthByteArrayLengthVarName + " = 2;\n";
		                methodsStr += "\t\t\t} else if (" + argDataLengthVarName + " <= 0xffff) {\n";
		                methodsStr += "\t\t\t\t//ex 0x82 0xff 0xff\n";
		                methodsStr += "\t\t\t\t" + argDataLengthByteArrayLengthVarName + " = 3;\n";
		                methodsStr += "\t\t\t} else if (" + argDataLengthVarName + " <= 0xffffff) {\n";
		                methodsStr += "\t\t\t\t//ex 0x83 0xff 0xff 0xff\n";
		                methodsStr += "\t\t\t\t" + argDataLengthByteArrayLengthVarName + " = 4;\n";
		                methodsStr += "\t\t\t}\n";
		                methodsStr += "\t\t}\n";
		                methodsStr += "\t\tdataLength += " + argDataLengthVarName + " + " + argDataLengthByteArrayLengthVarName + ";\n";
		            }
		            methodsStr += "\t\t//\n";
		            methodsStr += "\t\trequest.setLength(4 + dataLength);\n";
		            methodsStr += "\t\t//connect to server\n";
		            methodsStr += "\t\tTcpClient tcpClient = TcpClientFactory.create();\n";
		            methodsStr += "\t\ttcpClient.connect(host, port);\n";
		            methodsStr += "\t\t//serialize request according to HTNP\n";
		            methodsStr += "\t\tProtocol protocol = ProtocolFactory.create();\n";
		            methodsStr += "\t\tbyte[] serializedRequest = protocol.serializeRequest(request);\n";
		            methodsStr += "\t\t//send request\n";
		            methodsStr += "\t\ttcpClient.write(serializedRequest);\n";
		            methodsStr += "\t\t//read response from server\n";
		            methodsStr += "\t\tbyte[] buffer = new byte[256];\n";
		            methodsStr += "\t\twhile (!protocol.IsResponseComplete()) {\n";
		            methodsStr += "\t\t\tbyte[] dataChunkRead = tcpClient.read();\n";
		            methodsStr += "\t\t\tprotocol.processDataForResponse(dataChunkRead);\n";
		            methodsStr += "\t\t}\n";
		            methodsStr += "\t\t//deserialize token part of response\n";
		            methodsStr += "\t\tResponse response = protocol.getResponse();\n";
		            methodsStr += "\t\t//close everything\n";
		            methodsStr += "\t\t//deserialize " + pMethod->returnType_ +  "part from response\n";
		            std::string lowerCaseReturnType = pMethod->returnType_;
		            lowerCaseReturnType[0] += 32;
		            methodsStr += "\t\t"+pMethod->returnType_ + " " + lowerCaseReturnType + "= null;\n";
		            methodsStr += "\t\tif (response.getStatusCode() == -1) {\n";
		            methodsStr += "\t\t\t//throw exception\n";
		            methodsStr += "\t\t} else {\n";
		            methodsStr += "\t\t\t" + lowerCaseReturnType + "= new " + pMethod->returnType_ + "();\n";
		            methodsStr += "\t\t\t" + lowerCaseReturnType + ".deserialize(response.getData());\n";
		            methodsStr += "\t\t}\n";
		            methodsStr += "\t\treturn " + lowerCaseReturnType + ";\n";
		            methodsStr += "\t}\n";
		        }
		        replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%METHODS%]"),11,methodsStr);
		        os.write(replacableServiceProxyStrTmp.c_str(), replacableServiceProxyStrTmp.size());
		        os.close();
		    }
			/*  sample code for [%METHODS%]
			                      public Token authenticate(Credential credential) throws Exception {

			                 //serialize credential
			                 byte[] serializedCredential = credential.serialize();

			                 //make request
			                 Request request = new Request();
			                 request.setServiceId((byte) 1);
			                 request.setMethodId((byte) 1);
			                 request.setArgumentCount((byte) 1);
			                 request.setType(Request.RequestType.InvokeStateless);
			                 Argument arg = new Argument();
			                 arg.setDataLength(credential.serialize().length);
			                 arg.setData(credential.serialize());
			                 request.addArgument(arg);


			                 int dataLength = 0;
			                //calculate data length for every argument
			                //credential
			                int credentialDataLength = serializedCredential.length;
			                int credentialDataLengthByteArrayLength = 1;
			                if (credentialDataLength >= 0x80) {
			                    if (credentialDataLength <= 0xff) {
			                        //ex 0x81 0xff
			                        credentialDataLengthByteArrayLength = 2;
			                    } else if (credentialDataLength <= 0xffff) {
			                        //ex 0x82 0xff 0xff
			                        credentialDataLengthByteArrayLength = 3;
			                    } else if (credentialDataLength <= 0xffffff) {
			                        //ex 0x83 0xff 0xff 0xff
			                        credentialDataLengthByteArrayLength = 4;
			                    }
			                }
			                dataLength += credentialDataLength + credentialDataLengthByteArrayLength;
			                //
			                request.setLength(4 + dataLength);


			                 //connect to ir.ntnaeem.hottentot.server
			                 TcpClient tcpClient = TcpClientFactory.create();
			                 tcpClient.connect(host, port);
			                 //serialize request according to HTNP


			                 Protocol protocol = ProtocolFactory.create();
			                 byte[] serializedRequest = protocol.serializeRequest(request);

			                 //send request
			                 tcpClient.write(serializedRequest);
			                 //read response from ir.ntnaeem.hottentot.server
			                 byte[] buffer = new byte[256];
			                 while (!protocol.IsResponseComplete()) {

			                     byte[] dataChunkRead = tcpClient.read();
			                     protocol.processDataForResponse(dataChunkRead);
			                 }
			                 //deserialize token part of response
			                 Response response = protocol.getResponse();
			                 //close everything

			                 //deserialize token part from response
			                 Token token = null;


			                 //***********
			                 //*************
			                 if (response.getStatusCode() == -1) {
			                     //throw exception
			                 } else {
			                     token = new Token();
			                     token.deserialize(response.getData());
			                 }
			                 return token;

			                 }
			*/
		}

		
      }
    }
  }
}
