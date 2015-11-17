//
// Created by alisharifi on 11/10/15.
//

#include "hot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "service.h"

Hot::~Hot() {
    //TODO delete all in madules_
};

void
Hot::FakeInsert() {
    //fake insert
    Module *modulePtr = new Module();
    modulePtr->name_ = "ir.ntnaeem.hottentot.generated";
    //Credential struct
    Struct *credStructPtr = new Struct();
    credStructPtr->name_ = "Credential";
    Member *usernameMemberPtr = new Member();
    usernameMemberPtr->type_ = "String";
    usernameMemberPtr->name_ = "username";
    Member *passwordMemberPtr = new Member();
    passwordMemberPtr->type_ = "String";
    passwordMemberPtr->name_ = "password";
    credStructPtr->members_.push_back(usernameMemberPtr);
    credStructPtr->members_.push_back(passwordMemberPtr);

    modulePtr->structs_.push_back(credStructPtr);

    //Token struct
    Struct *tokenStructPtr = new Struct();
    tokenStructPtr->name_ = "Token";
    Member *valueMemberPtr = new Member();
    valueMemberPtr->type_ = "String";
    valueMemberPtr->name_ = "value";
    tokenStructPtr->members_.push_back(valueMemberPtr);
    modulePtr->structs_.push_back(tokenStructPtr);

    //authenticate service
    Service *authServicePtr = new Service();
    authServicePtr->name_ = "Authentication";
    authServicePtr->id_ = 1;
    authServicePtr->requestType_ = 3;
    Method *methodPtr = new Method();
    methodPtr->id_ = 1;
    methodPtr->name_ = "authenticate";
    Argument *credentialArgPtr = new Argument();
    credentialArgPtr->type_ = "Credential";
    credentialArgPtr->name_ = "credential";
    methodPtr->args_.push_back(credentialArgPtr);
    methodPtr->returnType_ = "Token";
    authServicePtr->methods_.push_back(methodPtr);
    modulePtr->services_.push_back(authServicePtr);
    modules_.push_back(modulePtr);
}

void
Hot::ReadTemplateFiles() {
    //using the ds to write .hot file

    //TODO use buffer reading
//    char buffer[100];
//    FILE* f = fopen("/home/developer/Desktop/templates/struct.tmp","rb");
//    string str;
//    while(true){
//        unsigned int r = fread(buffer , sizeof(char), 10 ,f);
//        str += reinterpret_cast< char const* >(buffer);
//        if(r == 0){
//            break;
//        }
//    }
//    cout << str;
//    fclose(f);
//    f = fopen("/home/developer/Desktop/templates/new.tmp","wb");
//    fwrite(str.c_str() , sizeof(char), str.length(),f);
//    fclose(f);


    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/struct.tmp", ios::in);
    //TODO use buffer reader
    char c;
    while ((c = is.get()) != -1) {
        structTmpStr_ += c;
    }
    is.close();
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/abstractService.tmp", ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        abstractServiceTmpStr_ += c;
    }
    is.close();

    //service interface
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/service.tmp", ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        serviceTmpStr_ += c;
    }
    is.close();
    //service proxy
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/serviceProxy.tmp",
            ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        serviceProxyTmpStr_ += c;
    }
    is.close();

    //service proxy builder
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/serviceProxyBuilder.tmp",
            ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        serviceProxyBuilderTmpStr_ += c;
    }
    is.close();

    //request handler
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/requestHandler.tmp",
            ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        requestHandlerTmpStr_ += c;
    }
    is.close();
//    cout << structTmpStr_;
//    cout << abstractServiceTmpStr_;
//    cout << serviceTmpStr_;
//    cout << serviceProxyBuilderTmpStr_;
//    cout << serviceProxyTmpStr_;
//    cout << requestHandlerTmpStr_;
}

void
Hot::GenerateStructs(Module *modulePtr) {
    //loop on structs in everey module
    //cout << structTmpStr << endl << "-----" << endl;
    for (int i = 0; i < modulePtr->structs_.size(); i++) {
        Struct *aStruct = modulePtr->structs_.at(i);
        os.open("/home/developer/projects/hottentot-git/generator/java-generator/generated/" + aStruct->name_ +
                ".java");
        string basePackageName = modulePtr->name_;
        string replacableStructTmpStr = structTmpStr_;
        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%STRUCT_NAME%]"), 15, aStruct->name_);
        string memberDeclarationStr;
        string memberGetterSetterStr;
        for (int i = 0; i < aStruct->members_.size(); i++) {
            Member *memberPtr = aStruct->members_.at(i);
            string memberName = memberPtr->name_;
            string capitalizedMemberName = memberPtr->name_;
            capitalizedMemberName[0] -= 32;
            memberDeclarationStr += "\tprivate " + memberPtr->type_ + " " + memberName + ";\n";
            memberGetterSetterStr += "\tpublic void set" + capitalizedMemberName + "(" + memberPtr->type_ + " " + memberName + ") {\n";
            memberGetterSetterStr += "\t\tthis." + memberName + " = " + memberName + ";\n";
            memberGetterSetterStr += "\t}\n";
            memberGetterSetterStr += "\tpublic " + memberPtr->type_ + " get" + capitalizedMemberName + "() {\n";
            memberGetterSetterStr += "\t\treturn " + memberPtr->name_ + ";\n";
            memberGetterSetterStr += "\t}\n";
        }
        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%MEMBERS%]"), 11,
                                       memberDeclarationStr + memberGetterSetterStr);
        os.write(replacableStructTmpStr.c_str(), replacableStructTmpStr.size());
        os.close();
    }
}

void
Hot::GenerateAbstractService(Module *modulePtr) {
    //loop for every services
    Service *servicePtr;
    string replacableAbstractServiceTmpStr;
    for (int i = 0; i < modulePtr->services_.size(); i++) {
        //write abstractService.tmp
        string basePackageName = modulePtr->name_;
        servicePtr = modulePtr->services_.at(i);
        os.open("/home/developer/projects/hottentot-git/generator/java-generator/generated/Abstract" +
                servicePtr->name_ + "Service.java", ios::trunc);
        replacableAbstractServiceTmpStr = abstractServiceTmpStr_;
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                                basePackageName);
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                                basePackageName);
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                                basePackageName);
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                servicePtr->name_);
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                servicePtr->name_);
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                servicePtr->name_);
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                servicePtr->name_);
        stringstream ssID;
        ssID << servicePtr->id_;
        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_ID%]"), 14, ssID.str());
        os.write(replacableAbstractServiceTmpStr.c_str(), replacableAbstractServiceTmpStr.size());
        os.close();

//
    }
}

void
Hot::GenerateServiceInterface(Module *modulePtr) {
    Service *servicePtr;
    string replacableServiceTmpStr;
    for (int i = 0; i < modulePtr->services_.size(); i++) {
        //write abstractService.tmp
        string basePackageName = modulePtr->name_;
        servicePtr = modulePtr->services_.at(i);
        //write service interface
        string replacableServiceTmpStr = serviceTmpStr_;
        os.open("/home/developer/projects/hottentot-git/generator/java-generator/generated/" + servicePtr->name_ +
                "Service.java", ios::trunc);
        replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
        replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_NAME%]"), 16, servicePtr->name_);
        string serviceMethodsStr;
        //loop for service methods
        Method *methodPtr;
        for (int i = 0; i < servicePtr->methods_.size(); i++) {
            methodPtr = servicePtr->methods_.at(i);
            serviceMethodsStr += "\tpublic " + methodPtr->returnType_ + " " + methodPtr->name_ + "(";
            //loop on methods arguments
            Argument *pArg;
            for (int i = 0; i < methodPtr->args_.size(); i++) {
                pArg = methodPtr->args_.at(i);
                serviceMethodsStr +=  pArg->type_ + " " + pArg->name_;
                if (i < methodPtr->args_.size() - 1) {
                    serviceMethodsStr += ",";
                }
            }
            serviceMethodsStr += ") throws Exception;";
        };
        replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_METHODS%]"), 19, serviceMethodsStr);
        os.write(replacableServiceTmpStr.c_str(), replacableServiceTmpStr.size());
        os.close();
    }
}


void
Hot::GenerateServiceProxyBuilder(Module *pModule) {
    Service *servicePtr;
    string replacableServiceProxyBuilderTmpStr;
    for (int i = 0; i < pModule->services_.size(); i++) {
        //write abstractService.tmp
        string basePackageName = pModule->name_;
        servicePtr = pModule->services_.at(i);
        string replacableServiceProxyBuilderTmpStr;
        //write service proxy builder
        os.open("/home/developer/projects/hottentot-git/generator/java-generator/generated/" + servicePtr->name_ +
                "ServiceProxyBuilder.java", ios::trunc);
        replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr_;
        replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]"),
                                                    21,
                                                    basePackageName);
        replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]"),
                                                    21,
                                                    basePackageName);
        replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                    servicePtr->name_);
        replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                    servicePtr->name_);
        replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                    servicePtr->name_);
        replacableServiceProxyBuilderTmpStr.replace(replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16,
                                                    servicePtr->name_);
        os.write(replacableServiceProxyBuilderTmpStr.c_str(), replacableServiceProxyBuilderTmpStr.size());
        os.close();
    }

}

void
Hot::GenerateRequestHandler(Module *pModule) {
    Service *pService;
    string replacableRequestHandlerTmpStr;
    string basePackageName = pModule->name_;
    for (int i = 0; i < pModule->services_.size(); i++) {
        string basePackageName = pModule->name_;
        pService = pModule->services_.at(i);
        os.open("/home/developer/projects/hottentot-git/generator/java-generator/generated/" + pService->name_ +
                "RequestHandler.java");
        string serviceName = pService->name_;
        string lowerCaseServiceName = pService->name_;
        lowerCaseServiceName[0] += 32;
        replacableRequestHandlerTmpStr = requestHandlerTmpStr_;
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                               basePackageName);

        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16,
                                               serviceName);
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16,
                                               serviceName);
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16,
                                               serviceName);
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16,
                                               serviceName);
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME_LOWERCASE%]"), 26,
                                               lowerCaseServiceName);

        Method *pMethod;
        string methodConditionStr;

        for (int i = 0; i < pService->methods_.size(); i++) {
            pMethod = pService->methods_.at(i);
            string lowerCaseReturnType = pMethod->returnType_;
            lowerCaseReturnType[0] += 32;
            stringstream ssID;
            ssID << pMethod->id_;
            methodConditionStr += "if(methodId == " + ssID.str() + "){\n";
            methodConditionStr += "\t\tList <Argument> args = request.getArgs();\n";
            Argument *pArg;
            for (int i = 0; i < pMethod->args_.size(); i++) {
                pArg = pMethod->args_.at(i);
                stringstream ssI;
                ssI << i;
                methodConditionStr += "\t\tArgument arg" + ssI.str() + " = args.get(" + ssI.str() + ");\n";
                methodConditionStr += "\t\tbyte[] serialized" + pArg->type_;
                methodConditionStr += " = arg" + ssI.str() + ".getData();\n";
                methodConditionStr += "\t\t" + pArg->type_ + " " + pArg->name_ + " = new " + pArg->type_ + "();\n";
                methodConditionStr += "\t\t" + pArg->name_ + ".deserialize(serialized" + pArg->type_ + ");\n";
            }
            methodConditionStr += "\t\t" + pMethod->returnType_ + " " + lowerCaseReturnType + " = null;\n";
            methodConditionStr += "\t\tResponse response = new Response();\n";
            methodConditionStr += "\t\ttry{\n";
            methodConditionStr +=
                    "\t\t\t" + lowerCaseReturnType + " = " + lowerCaseServiceName + "Impl." + pMethod->name_ + "(";
            for (int i = 0; i < pMethod->args_.size(); i++) {
                pArg = pMethod->args_.at(i);
                methodConditionStr += pArg->name_;
                if (i < pMethod->args_.size() - 1) {
                    methodConditionStr += pArg->name_ += ",";
                }
            }
            methodConditionStr += ");\n";
            methodConditionStr +=
                    "\t\t\tbyte[] serialized" + pMethod->returnType_ + " = " + lowerCaseReturnType + ".serialize();\n";
            methodConditionStr += "\t\t\tresponse.setStatusCode((byte) 100);\n";
            methodConditionStr += "\t\t\tresponse.setData(serialized" + pMethod->returnType_ + ");\n";
            methodConditionStr += "\t\t\tresponse.setLength(serialized" + pMethod->returnType_ + ".length + 1);\n";
            methodConditionStr += "\t\t} catch (Exception e) {\n";
            methodConditionStr += "\t\t\te.printStackTrace();\n";
            methodConditionStr += "\t\t}\n";
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
Hot::GenerateServiceProxy(Module *pModule) {
    Service *pService;
    string basePackageName = pModule->name_;
    for (int i = 0; i < pModule->services_.size(); i++) {
        string replacableServiceProxyStrTmp = serviceProxyTmpStr_;
        pService = pModule->services_.at(i);
        os.open("/home/developer/projects/hottentot-git/generator/java-generator/generated/" + pService->name_ +
                "ServiceProxy.java");
        pService = pModule->services_.at(i);
        replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%SERVICE_NAME%]"),
                                             16,
                                             pService->name_);
        replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%SERVICE_NAME%]"),
                                             16,
                                             pService->name_);
        replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%SERVICE_NAME%]"),
                                             16,
                                             pService->name_);
        replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%BASE_PACKAGE_NAME%]"),
                                             21,
                                             basePackageName);

        //loop on service methods
        Method *pMethod;
        string methodsStr;
        for (int i = 0; i < pService->methods_.size(); i++) {
            pMethod =  pService->methods_.at(i);
            pMethod = pService->methods_.at(i);
            methodsStr += "public " + pMethod->returnType_ + " " + pMethod->name_ + "(";
            Argument *pArg;
            for (int i = 0; i < pMethod->args_.size(); i++) {

                pArg = pMethod->args_.at(i);
                methodsStr += pArg->type_ + " " + pArg->name_;
                if (i < pMethod->args_.size() - 1) {
                    methodsStr += ",";
                }
            }
            methodsStr += ") throws Exception { \n";
            for (int i = 0; i < pMethod->args_.size(); i++) {
                methodsStr += "\t\t//serialize " + pArg->name_ + "\n";
                methodsStr += "\t\tbyte[] serialized" + pArg->type_ + " = " + pArg->name_ + ".serialize();\n";
            }
            methodsStr += "\n";
            methodsStr += "\t\t//make request\n";
            methodsStr += "\t\tRequest request = new Request();\n";
            stringstream serviceId;
            serviceId << pService->id_;
            methodsStr += "\t\trequest.setServiceId((byte) " + serviceId.str() + ");\n";
            stringstream methodId;
            methodId << pMethod->id_;
            methodsStr += "\t\trequest.setMethodId((byte) " + methodId.str() + ");\n";
            stringstream argSize;
            argSize << pMethod->args_.size();
            methodsStr += "\t\trequest.setArgumentCount((byte) " + argSize.str() + ");\n";
            methodsStr += "\t\trequest.setType(Request.RequestType.";
            if(pService->requestType_ == 1) {
                methodsStr += "Unknown";
            }else if(pService->requestType_ == 2){
                methodsStr += "ServiceListQuery";
            }else if(pService->requestType_ == 3){
                methodsStr += "InvokeStateless";
            }else if(pService->requestType_ == 4){
                methodsStr += "InvokeStatefull";
            }
            methodsStr += ");\n";
            for (int i = 0; i < pMethod->args_.size(); i++) {
                stringstream ssI;
                pArg = pMethod->args_.at(i);
                ssI << i;
                methodsStr += "\t\tArgument arg" + ssI.str() + " = new Argument();\n";
                methodsStr += "\t\targ" + ssI.str() + ".setDataLength(" + pArg->name_.c_str() + ".serialize().length);\n";
                methodsStr += "\t\targ" + ssI.str() + ".setData(" + pArg->name_.c_str() + ".serialize());\n";
                methodsStr += "\t\trequest.addArgument(arg" + ssI.str() + ");\n";
            }
            //calculate request length
            methodsStr += "\t\tint dataLength = 0;\n";
            methodsStr += "\t\t//calculate data length for every argument\n";
            for(int i= 0 ; i < pMethod->args_.size() ; i++){
                pArg = pMethod->args_.at(i);
                string argDataLengthVarName =  pArg->name_ + "DataLength";
                string argDataLengthByteArrayLengthVarName =  pArg->name_ + "DataLengthByteArrayLength";
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
            string lowerCaseReturnType = pMethod->returnType_;
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

void
Hot::GenerateJava() {
    FakeInsert();
    ReadTemplateFiles();
    Struct *aStructPtr;
    for (int i = 0; i < modules_.size(); i++) {
        Module *pModule = modules_.at(i);
        GenerateStructs(pModule);
        GenerateAbstractService(pModule);
        GenerateServiceInterface(pModule);
        GenerateServiceProxyBuilder(pModule);
        GenerateRequestHandler(pModule);
        GenerateServiceProxy(pModule);
    }
}