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
    modulePtr->name_ = "ir.naeem.hottentot.generated";
    //Credential struct
    Struct *credStructPtr = new Struct();
    credStructPtr->name_ = "Credential";
    Member *usernameMemberPtr = new Member();
    usernameMemberPtr->type_ = "string";
    usernameMemberPtr->name_ = "username";
    Member *passwordMemberPtr = new Member();
    passwordMemberPtr->type_ = "string";
    passwordMemberPtr->name_ = "password";
    credStructPtr->members_.push_back(usernameMemberPtr);
    credStructPtr->members_.push_back(passwordMemberPtr);
    modulePtr->structs_.push_back(credStructPtr);

    //Token struct
    Struct *tokenStructPtr = new Struct();
    tokenStructPtr->name_ = "Token";
    Member *valueMemberPtr = new Member();
    valueMemberPtr->type_ = "string";
    valueMemberPtr->name_ = "value";
    tokenStructPtr->members_.push_back(valueMemberPtr);
    modulePtr->structs_.push_back(tokenStructPtr);

    //authenticate service
    Service *authServicePtr = new Service();
    authServicePtr->name_ = "Authentication";
    authServicePtr->id_ = 1;
    Method *methodPtr = new Method();
    methodPtr->id_ = 1;
    methodPtr->name_ = "authenticate";
    Argument *credentialArgPtr = new Argument();
    credentialArgPtr->type_ = "Credential";
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
        structTmpStr += c;
    }
    is.close();
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/abstractService.tmp", ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        abstractServiceTmpStr += c;
    }
    is.close();
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/service.tmp", ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        serviceTmpStr += c;
    }
    is.close();
    //service proxy builder
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/serviceProxyBuider.tmp",
            ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        serviceProxyBuilderTmpStr += c;
    }
    is.close();

    //request handler
    is.open("/home/developer/projects/hottentot-git/generator/java-generator/templates/requestHandler.tmp",
            ios::in);
    //TODO use buffer reader
    while ((c = is.get()) != -1) {
        requestHandlerTmpStr += c;
    }
    is.close();
//    cout << structTmpStr;
//    cout << abstractServiceTmpStr;
//    cout << serviceTmpStr;
//    cout << serviceProxyBuilderTmpStr;
//    cout << requestHandlerTmpStr;
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
        string replacableStructTmpStr = structTmpStr;
        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%STRUCT_NAME%]"), 15, aStruct->name_);
        string memberDeclarationStr;
        string memberGetterSetterStr;
        for (int i = 0; i < aStruct->members_.size(); i++) {
            Member *memberPtr = aStruct->members_.at(i);
            string memberName = memberPtr->name_;
            memberPtr->name_[0] -= 32;
            string capitalizedMemberName = memberPtr->name_;
            memberPtr->name_ = memberName;
            memberDeclarationStr += "\tprivate " + memberPtr->type_ + " " + memberName + ";\n";
            memberGetterSetterStr +=
                    "\tpublic void set" + capitalizedMemberName + "(" + memberPtr->type_ + " " + memberName + ") {\n";
            memberGetterSetterStr += "\t\tthis." + memberName + " = " + memberName + "\n";
            memberGetterSetterStr += "\t}\n";
            memberGetterSetterStr += "\tpublic " + memberPtr->type_ + " get" + capitalizedMemberName + "() {\n";
            memberGetterSetterStr += "\t\treturn " + memberPtr->name_ + "\n";
            memberGetterSetterStr += "\t}";
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
        replacableAbstractServiceTmpStr = abstractServiceTmpStr;
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
        string replacableServiceTmpStr = serviceTmpStr;
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
            Argument *argPtr;
            for (int i = 0; i < methodPtr->args_.size(); i++) {
                argPtr = methodPtr->args_.at(i);
                string argType = argPtr->type_;
                argPtr->type_[0] += 32;
                string argName = argPtr->type_;
                argPtr->type_ = argType;
                serviceMethodsStr += argType + " " + argName;
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
        replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr;
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
                "RequestHandler.java");;
        string serviceName = pService->name_;
        pService->name_[0] += 32;
        string lowerCaseServiceName = pService->name_;
        replacableRequestHandlerTmpStr = requestHandlerTmpStr;
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                                               basePackageName);
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
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16,
                                               serviceName);
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%SERVICE_NAME_LOWERCASE%]"), 26,
                                               lowerCaseServiceName);

        Method *pMethod;
        string methodConditionStr;

        for (int i = 0; i < pService->methods_.size(); i++) {
            pMethod = pService->methods_.at(i);
            string returnType = pMethod->returnType_;
            pMethod->returnType_[0] += 32;
            string returnTypeLowerCase = pMethod->returnType_;
            pMethod->returnType_ = returnType;
            stringstream ssID;
            ssID << pMethod->id_;
            methodConditionStr += "if(methodId == " + ssID.str() + "){\n";
            methodConditionStr += "\t\tList <Argument> args = request.getArgs();\n";
            Argument *pArg;
            for (int i = 0; i < pMethod->args_.size(); i++) {
                pArg = pMethod->args_.at(i);
                stringstream ssI;
                ssI << i;
                methodConditionStr += "\t\tArgument arg" + ssI.str() + " = args.get(" + ssI.str() + ")\n";

                string argType = pArg->type_;
                pArg->type_[0] += 32;
                string argName = pArg->type_;
                pArg->type_ = argType;
                methodConditionStr += "\t\tbyte[] serialized" + argType;
                methodConditionStr += " = arg" + ssI.str() + ".getData();\n";
                methodConditionStr += "\t\t" + argType + " " + argName + " = new " + argType + "();\n";
                methodConditionStr += "\t\t" + argName + ".deserialize(serialized" + argType + ")\n";
            }
            methodConditionStr += "\t\t" + returnType + " " + returnTypeLowerCase + " = null;\n";
            methodConditionStr += "\t\tResponse response = new Response();\n";
            methodConditionStr += "\t\ttry{\n";
            methodConditionStr += "\t\t\t"+ returnTypeLowerCase +" = " + lowerCaseServiceName + "Impl." + pMethod->name_ + "(";
            for (int i = 0; i < pMethod->args_.size(); i++) {
                pArg = pMethod->args_.at(i);
                string argType = pArg->type_;
                pArg->type_[0] += 32;
                string argName = pArg->type_;
                if (i < pMethod->args_.size() - 1) {
                    methodConditionStr += argName + ",";
                }
            }
            methodConditionStr += ");\n";
            methodConditionStr +=
                    "\t\t\tbyte[] serialized" + returnType + " = " + returnTypeLowerCase + ".serialize();\n";
            methodConditionStr += "\t\t\tresponse.setStatusCode((byte) 100);\n";
            methodConditionStr += "\t\t\tresponse.setData(serialized" + returnType + ");\n";
            methodConditionStr += "\t\t\tresponse.setLength(serialized" + returnType + ".length + 1);\n";
            methodConditionStr += "\t\t} catch (Exception e) {\n";
            methodConditionStr += "\t\t\te.printStackTrace();\n";
            methodConditionStr += "\t\t}\n";
            methodConditionStr += "\t\treturn response;\n";
            methodConditionStr += "\t}";

        }
        replacableRequestHandlerTmpStr.replace(replacableRequestHandlerTmpStr.find("[%METHOD_CONDITIONS%]"),21,methodConditionStr);
        os.write(replacableRequestHandlerTmpStr.c_str(), replacableRequestHandlerTmpStr.size());
        os.close();
    }



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
        //TODO generate serviceProxy
    }
}