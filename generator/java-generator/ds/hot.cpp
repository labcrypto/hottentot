//
// Created by alisharifi on 11/10/15.
//

#include "hot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "service.h"


void
Hot::GenerateStructFiles() {

}

void
Hot::GenerateJava() {
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
    methodPtr->name_ = "authenticate";
    Argument *credentialArgPtr = new Argument();
    credentialArgPtr->type_ = "Credential";
    methodPtr->args_.push_back(credentialArgPtr);
    methodPtr->returnType_ = "Token";
    authServicePtr->methods_.push_back(methodPtr);
    modulePtr->services_.push_back(authServicePtr);


    modules_.push_back(modulePtr);







    //using the ds to write .hot file
    ifstream is;
    is.open("/home/developer/Desktop/templates/struct.tmp", ios::in);
    //TODO use buffer reader
    string structTmpStr;
    char c;
    while ((c = is.get()) != -1) {
        structTmpStr += c;
    }
    is.close();
    is.open("/home/developer/Desktop/templates/abstractService.tmp", ios::in);
    //TODO use buffer reader
    string abstractServiceTmpStr;
    while ((c = is.get()) != -1) {
        abstractServiceTmpStr += c;
    }
    is.close();
    is.open("/home/developer/Desktop/templates/service.tmp", ios::in);
    //TODO use buffer reader
    string serviceTmpStr;
    while ((c = is.get()) != -1) {
        serviceTmpStr += c;
    }
    is.close();
    //service proxy builder
    is.open("/home/developer/Desktop/templates/serviceProxyBuider.tmp", ios::in);
    //TODO use buffer reader
    string serviceProxyBuilderTmpStr;
    while ((c = is.get()) != -1) {
        serviceProxyBuilderTmpStr += c;
    }
    is.close();
    cout << structTmpStr;
    cout << abstractServiceTmpStr;
    cout << serviceTmpStr;
    cout << serviceProxyBuilderTmpStr;












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




    ofstream os;
    Struct *aStructPtr;
    for (int i = 0; i < modules_.size(); i++) {
        modulePtr = modules_.at(i);
        string basePackageName = modulePtr->name_;
        structTmpStr.replace(structTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
        //loop for every struct
        for (i = 0; i < modulePtr->structs_.size(); i++) {
            aStructPtr = modulePtr->structs_.at(i);
            os.open("/home/developer/Desktop/templates/" + aStructPtr->name_ + ".java", ios::trunc);
            cout << aStructPtr->name_ + ".java credeted" << endl;
            string temp = structTmpStr;
            structTmpStr.replace(structTmpStr.find("[%STRUCT_NAME%]"), 14, aStructPtr->name_);
            cout << structTmpStr;
            string memberDeclarationsStr;
            string membersSetterGetterStr;
            Member *member;
            //loop for members
            for (int i = 0; i < aStructPtr->members_.size(); i++) {
                member = aStructPtr->members_.at(i);
                //property declarations
                memberDeclarationsStr += "\tprivate " + member->type_ + " " + member->name_ + ";\n";
                string memberName = member->name_;
                member->name_[0] -= 32;
                string capitalizedMemberName = member->name_;
                //getter
                membersSetterGetterStr +=
                        "\tpublic " + member->type_ + " get" + capitalizedMemberName + "() {\n\t\treturn " +
                        member->name_ + ";\n\t}\n";
                membersSetterGetterStr +=
                        "\tpublic void set" + capitalizedMemberName + "(" + member->type_ + " " + memberName +
                        "){\n\t\tthis." + memberName + "=" + memberName + ";\n\t}\n";
            }


            structTmpStr.replace(structTmpStr.find("[%MEMBERS%]"), 8,
                                 memberDeclarationsStr + "\n" + membersSetterGetterStr);
            os.write(structTmpStr.c_str(), structTmpStr.size());
            structTmpStr = temp;
            os.close();
            //delete member;
        }
        //loop for every services
        Service *servicePtr;
        cout <<  "++++++" << modules_.at(0)->services_.size() << endl;
        for (int i = 0; i < modulePtr->services_.size(); i++) {
            //write abstractService.tmp

            servicePtr = modulePtr->services_.at(i);

            os.open("/home/developer/Desktop/templates/Abstract" + servicePtr->name_ + "Service.java", ios::trunc);
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
            cout << servicePtr->name_;
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16, servicePtr->name_);
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16, servicePtr->name_);
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16, servicePtr->name_);
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%SERVICE_NAME%]"), 16, servicePtr->name_);
            stringstream ssID;
            ssID << servicePtr->id_;
            abstractServiceTmpStr.replace(abstractServiceTmpStr.find("[%SERVICE_ID%]"), 14, ssID.str());
            os.write(abstractServiceTmpStr.c_str(), abstractServiceTmpStr.size());
            os.close();
            //write service interface
            os.open("/home/developer/Desktop/templates/" + servicePtr->name_ + "Service.java", ios::trunc);
            serviceTmpStr.replace(serviceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
            serviceTmpStr.replace(serviceTmpStr.find("[%SERVICE_NAME%]"), 16, basePackageName);
            string serviceMethodsStr;
            //loop for service methods
            for (int i = 0; i < servicePtr->methods_.size(); i++) {
                methodPtr = servicePtr->methods_.at(i);
                serviceMethodsStr += "\tpublic " + methodPtr->returnType_ + " " + methodPtr->name_ + "(";
                //loop on methods arguments
                Argument* argPtr;
                for (int i = 0; i < methodPtr->args_.size(); i++) {
                    argPtr = methodPtr->args_.at(i);
                    string argType = argPtr->type_;
                    argPtr->type_[0] += 32;
                    string argName = argPtr->type_;
                    serviceMethodsStr += argType+" "+argName;
                    if( i < methodPtr->args_.size() -1){
                        serviceMethodsStr += ",";
                    }
                }
                serviceMethodsStr += ") throws Exception;";
            };
            serviceTmpStr.replace(serviceTmpStr.find("[%SERVICE_METHODS%]"),19,serviceMethodsStr);
            os.write(serviceTmpStr.c_str() , serviceTmpStr.size());
            os.close();
            //write service proxy builder
            os.open("/home/developer/Desktop/templates/" + servicePtr->name_ + "ServiceProxyBuilder.java", ios::trunc);
            serviceProxyBuilderTmpStr.replace(serviceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]"),21,basePackageName);
            serviceProxyBuilderTmpStr.replace(serviceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"),16,servicePtr->name_);
            serviceProxyBuilderTmpStr.replace(serviceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"),16,servicePtr->name_);
            serviceProxyBuilderTmpStr.replace(serviceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"),16,servicePtr->name_);
            serviceProxyBuilderTmpStr.replace(serviceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"),16,servicePtr->name_);
            os.write(serviceProxyBuilderTmpStr.c_str(),serviceProxyBuilderTmpStr.size());
            os.close();
        }

    }




    //destroy
    //TODO delete all pointer
    //os.close();
    is.close();
    delete modulePtr;

    //TODO
    //delete membes



}