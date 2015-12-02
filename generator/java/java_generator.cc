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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANindent_ILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "java_generator.h"
#include "../ds/hot.h"
#include <stdint.h>
#include <sys/stat.h>
#include <sstream>
#include "../common/string_helper.h"
#include "../common/os.h" 
#include "../common/type_helper.h" 
#include "templates/byte_arrays/abstractService.h" 
#include "templates/byte_arrays/requestHandler.h" 
#include "templates/byte_arrays/service.h" 
#include "templates/byte_arrays/serviceProxy.h" 
#include "templates/byte_arrays/serviceProxyBuilder.h" 
#include "templates/byte_arrays/struct.h" 

 namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {

        JavaGenerator::~JavaGenerator() {
                    //TODO change vector to map 

                    // for (int i = 0; i < modules_.size(); i++) {
                    //     ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);
                    //     for (int j = 0; j < pModule->structs_.size(); j++) {
                    //         ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(j);
                    //         for (int k = 0; k < pStruct->declarations_.size(); k++) {
                    //             delete pStruct->declarations_.at(k);
                    //         }
                    //         delete pStruct;
                    //     }
                    //     delete pModule;
                    // }
        }
        
        void
        JavaGenerator::Destroy(){
                    //TODO

                    // for (int i = 0; i < modules_.size(); i++) {
                    //     ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);
                    //     for (int j = 0; j < pModule->structs_.size(); j++) {
                    //         ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(j);
                    //         for (int k = 0; k < pStruct->declarations_.size(); k++) {
                    //             delete pStruct->declarations_.at(k);
                    //         }
                    //         delete pStruct;
                    //     }
                    //     delete pModule;
                    // }
        }


        JavaGenerator::JavaGenerator() {

                    //MakeStringsFromByteArrays();
                    //ReadTemplateFiles();
        }

        void
        JavaGenerator::MakeTabStr(::naeem::hottentot::generator::GenerationConfig &generationConfig){
          outDir_ = generationConfig.outDir_;
          if(generationConfig.IsSpacesUsedInsteadOfTabsForIndentation()) {
            for (int i = 0; i < generationConfig.GetNumberOfSpacesUsedForIndentation() ; i++) {
              indent_ += " ";
            }
          }else{
            indent_ = "\t";
          }
        }

        void
        JavaGenerator::Generate(::naeem::hottentot::generator::ds::Hot *hot,
          ::naeem::hottentot::generator::GenerationConfig &generationConfig) {
          MakeTabStr(generationConfig);
          ::naeem::hottentot::generator::common::Os::MakeDir(outDir_.c_str());
          modules_ = hot->modules_;
          for (int i = 0; i < modules_.size(); i++) {
            ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);
            GenerateStructs(pModule);
            GenerateAbstractService(pModule);
            GenerateServiceInterface(pModule);
            GenerateRequestHandler(pModule);
            GenerateServiceProxyBuilder(pModule);
            GenerateServiceProxy(pModule);
          }
          std::cout << "Java Generation done." << std::endl;
          Destroy();
        }

        

        uint32_t
        JavaGenerator::GetTypeLength(std::string type){
          if (type.compare("int8") == 0 ||
            type.compare("uint8") == 0) {
            return 1;
        } else if (type.compare("int16") == 0 ||
         type.compare("uint16") == 0) {
          return 2;
        } else if (type.compare("int32") == 0 ||
         type.compare("uint32") == 0) {
          return 4;
        } else if (type.compare("int64") == 0 ||
         type.compare("uint64") == 0) {
          return 8;
        }
      }

      void
      JavaGenerator::ReadTemplateFiles() {
        ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/struct.template",structTmpStr_);
        ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/abstractService.template",abstractServiceTmpStr_);
        ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/service.template",serviceTmpStr_);
        ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/serviceProxy.template",serviceProxyTmpStr_);
        ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/serviceProxyBuilder.template",serviceProxyBuilderTmpStr_);
        ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/requestHandler.template",requestHandlerTmpStr_);
//			std::cout << "---------------" << std::endl;
//			std::cout << structTmpStr_;
//			std::cout << abstractServiceTmpStr_`//			std::cout << serviceTmpStr_;
//			std::cout << serviceProxyBuilderTmpStr_;
//			std::cout << serviceProxyTmpStr_;
//			std::cout << requestHandlerTmpStr_;
      }

      void
      JavaGenerator::GenerateStructs(::naeem::hottentot::generator::ds::Module *pModule) {
                    //loop on structs in everey module
        for (int i = 0; i < pModule->structs_.size(); i++) {
          ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(i);
          std::string basePackageName = pModule->package_;
          std::string replacableStructTmpStr = structTmpStr;

          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%INDENT%]" , indent_ , 1);
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%STRUCT_NAME%]" , pStruct->name_ , 1);
                        // while (replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableStructTmpStr.replace(replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                        //                                    basePackageName);
                        // }
                        // while (replacableStructTmpStr.find("[%STRUCT_NAME%]") != std::string::npos) {
                        //     replacableStructTmpStr.replace(replacableStructTmpStr.find("[%STRUCT_NAME%]"), 15,
                        //                                    pStruct->name_);
                        // }
          std::string declarationStr;
          std::string getterSetterStr;
          std::string declarationJavaType;
          std::string capitalizedDeclarationJavaType;

          for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
           = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
          declarationJavaType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(declarationPtr->type_);
          capitalizedDeclarationJavaType  = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationJavaType);
          std::string declarationName = declarationPtr->variable_;
          std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->variable_);
          declarationStr +=
          indent_ + "private " + declarationJavaType + " " + declarationName + ";\n";
          getterSetterStr += indent_ + "public void set" + capitalizedDeclarationName + "(" +
           declarationJavaType + " " + declarationName + ") {\n";
getterSetterStr +=
indent_ + indent_ + "this." + declarationName + " = " + declarationName + ";\n";
getterSetterStr += indent_ + "}\n";
getterSetterStr +=
indent_ + "public " + declarationJavaType + " get" + capitalizedDeclarationName +
"() {\n";
getterSetterStr += indent_ + indent_ + "return " + declarationPtr->variable_ + ";\n";
getterSetterStr += indent_ + "}\n";
}
replacableStructTmpStr.replace(replacableStructTmpStr.find("[%MEMBERS%]"), 11,
 declarationStr + getterSetterStr);

                        //serilize method
std::string serializeMethodStr;
for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
 = pStruct->declarations_.begin();
 it != pStruct->declarations_.end();
 ++it) {
  ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->variable_);
serializeMethodStr += indent_ + indent_ + "byte[] serialized" + capitalizedDeclarationName + " = PDTSerializer.get";
declarationJavaType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(declarationPtr->type_);
capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationJavaType);
std::string capitalizedDeclarationType  = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->type_);
serializeMethodStr += capitalizedDeclarationType + "(";
  serializeMethodStr += declarationPtr->variable_ + ");\n";
}
serializeMethodStr += indent_ + indent_ + "byte[] output = new byte[";
  for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
   = pStruct->declarations_.begin();
   it != pStruct->declarations_.end();
   ++it) {
    ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
  std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->variable_.c_str());
  serializeMethodStr += "serialized" + capitalizedDeclarationName + ".length";
  if (it->first == pStruct->declarations_.size()) {
    serializeMethodStr += "];\n";
} else {
  serializeMethodStr += " + ";
}
}

serializeMethodStr += indent_ + indent_ + "int counter = 0;\n";
serializeMethodStr += indent_ + indent_ + "//use a loop for every property\n";
for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
 = pStruct->declarations_.begin();
 it != pStruct->declarations_.end();
 ++it) {
  ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
declarationJavaType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(declarationPtr->type_);
capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationJavaType);
std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->variable_);
serializeMethodStr += indent_ + indent_ + "for (int i = 0; i < serialized" +
  capitalizedDeclarationName + ".length; i++) {\n";
serializeMethodStr += indent_ + indent_ + indent_ + "output[counter++] = serialized" +
capitalizedDeclarationName + "[i];\n";
serializeMethodStr += indent_ + indent_ + "}\n";
}
serializeMethodStr += indent_ + indent_ + "return output;";
                        //
replacableStructTmpStr.replace(replacableStructTmpStr.find("[%SERIALIZE_METHOD_BODY%]"), 25,
 serializeMethodStr);
                        // sample code
                              // byte[] serializedId = PDTSerializer.getInt16(id);
                              // byte[] serializedValue = PDTSerializer.getString(value);
                              // byte[] output = new byte[serializedId.length + serializedValue.length];
                              // int counter = 0;
                              // //use a loop for every property
                              // for (int i = 0; i < serializedId.length; i++) {
                              //     output[counter++] = serializedId[i];
                              // }
                              // for (int i = 0; i < serializedValue.length; i++) {
                              //     output[counter++] = serializedValue[i];
                              // }
                              // return output;


                        // deserialize method
std::string deserializeMethodStr;
deserializeMethodStr += indent_ + indent_ + "int counter = 0;\n";
deserializeMethodStr += indent_ + indent_ + "int dataLength = 0;\n";
deserializeMethodStr += indent_ + indent_ + "int numbersOfBytesForDataLength;\n";
deserializeMethodStr += indent_ + indent_ + "//do for every property\n";
for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
 = pStruct->declarations_.begin();
 it != pStruct->declarations_.end();
 ++it) {
  ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
declarationJavaType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(declarationPtr->type_);
std::string capitalizedDeclarationType = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->type_);
std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->variable_);
deserializeMethodStr += indent_ + indent_ + "//" + declarationPtr->variable_ + " : " + declarationJavaType + "\n";
if(declarationJavaType.compare("String") == 0) {
  deserializeMethodStr += indent_ + indent_ + "dataLength = 0;\n";
  deserializeMethodStr += indent_ + indent_ +
  "if(( serializedByteArray[counter] & 0x80) == 0 ) {\n";
  deserializeMethodStr += indent_ + indent_ + indent_ + "dataLength = serializedByteArray[counter++];\n";
  deserializeMethodStr += indent_ + indent_ + "}else{\n";             
  deserializeMethodStr += indent_ + indent_ + indent_ + "numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;\n";
  deserializeMethodStr += indent_ + indent_ + indent_ + "for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){\n";
  deserializeMethodStr += indent_ + indent_ + indent_ + indent_ + "dataLength += pow(256, numbersOfBytesForDataLength - i - 1) * serializedByteArray[counter++];\n";
  deserializeMethodStr += indent_ + indent_ + indent_ + "}\n";
  deserializeMethodStr += indent_ + indent_ + "}\n";
  deserializeMethodStr += indent_ + indent_ + "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[dataLength];\n";
  deserializeMethodStr += indent_ + indent_ + "System.arraycopy(serializedByteArray,counter," + declarationPtr->variable_.c_str() + "ByteArray,0,dataLength);\n";
  deserializeMethodStr += indent_ + indent_ + "counter += dataLength;\n";
  deserializeMethodStr += indent_ + indent_ + "set" + capitalizedDeclarationName + "(PDTDeserializer.get" + capitalizedDeclarationType + "(" + declarationPtr->variable_.c_str() + "ByteArray));\n";
}else {
  uint32_t dataLength = GetTypeLength(declarationPtr->type_.c_str());
  capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationJavaType);
  std::stringstream dataLengthStr;
  dataLengthStr << dataLength;
  deserializeMethodStr += indent_ + indent_ + "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[" + dataLengthStr.str() + "];\n";
  deserializeMethodStr += indent_ + indent_ + "for(int i = 0 ; i < " + dataLengthStr.str() + " ; i++){\n";
  deserializeMethodStr += indent_ + indent_ + indent_ + declarationPtr->variable_.c_str() + "ByteArray[i] = serializedByteArray[counter++];\n";            
  deserializeMethodStr += indent_ + indent_ + "}\n";
  deserializeMethodStr += indent_ + indent_ + "set" + capitalizedDeclarationName + "(PDTDeserializer.get" + capitalizedDeclarationType + "(" + declarationPtr->variable_.c_str() + "ByteArray));\n";
}
}

replacableStructTmpStr.replace(replacableStructTmpStr.find("[%DESERIALIZE_METHOD_BODY%]"),27,
  deserializeMethodStr);

                        //deserialize sample code 
                        /*
                        int counter = 0;
                        //do for every property
                        //value : string
                        int dataLength = 0 ;
                        int numbersOfBytesForDataLength;
                        if(serializedToken[counter] < 0x80){
                            dataLength = serializedToken[counter++];
                        }else{
                            numbersOfBytesForDataLength = serializedToken[counter++] & 0x0f;
                            for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
                                dataLength += pow(256, numbersOfBytesForDataLength - i - 1) * serializedToken[counter++];
                            }
                        }
                        byte[] valueByteArray = new byte[dataLength];
                        System.arraycopy(serializedToken,counter,valueByteArray,0,dataLength);
                        counter += dataLength;
                        setValue(PDTDeserializer.getString(valueByteArray));
                        //id : int16
                        byte[] idByteArray = new byte[2];
                        for(int i = 0 ; i < 2 ; i++){
                            idByteArray[i] = serializedToken[counter++];
                        }
                        setId(PDTDeserializer.getInt16(idByteArray));
                        */
                        std::string path = outDir_ + "/" + pStruct->name_.c_str() + ".java";
                        ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableStructTmpStr);
                      }
                    }

                    void
                    JavaGenerator::GenerateAbstractService(::naeem::hottentot::generator::ds::Module *pModule) {
                    //loop for every services
                      ::naeem::hottentot::generator::ds::Service *pService;
                      std::string replacableAbstractServiceTmpStr;
                      for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.template
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        std::string path = outDir_ + "/Abstract" + pService->name_.c_str() + "Service.java";
                        os.open(path.c_str(), std::ios::trunc);
                        replacableAbstractServiceTmpStr = abstractServiceTmpStr;

                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%INDENT%]" , indent_ , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
                        //get service ID from hot parser
                        std::stringstream ssID;
                        ssID << pService->GetHash();
                        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_ID%]"),
                          14, ssID.str());
                        os.write(replacableAbstractServiceTmpStr.c_str(), replacableAbstractServiceTmpStr.size());
                        os.close();
                      }
                    }

                    void
                    JavaGenerator::GenerateServiceInterface(::naeem::hottentot::generator::ds::Module *pModule) {
                      ::naeem::hottentot::generator::ds::Service *pService;
                      std::string replacableServiceTmpStr;
                      for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.template
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        //write service interface
                        std::string replacableServiceTmpStr = serviceTmpStr;
                        //std::cout << outDir_;
                        
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceTmpStr , "[%INDENT%]" , indent_ , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
                        // while (replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                        //                                     basePackageName);
                        // }
                        // while (replacableServiceTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                        //     replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_NAME%]"), 16,
                        //                                     pService->name_);
                        // }
                        std::string serviceMethodsStr;
                        //loop for service methods
                        ::naeem::hottentot::generator::ds::Method *pMethod;
                        for (int i = 0; i < pService->methods_.size(); i++) {
                          pMethod = pService->methods_.at(i);
                          if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)){
                            serviceMethodsStr += indent_ + "" + pMethod->returnType_ + " " + pMethod->name_ + "(";    
                          }else{
                            std::string returnType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pMethod->returnType_);
                            serviceMethodsStr += indent_ + "" + returnType + " " + pMethod->name_ + "(";
                          }
                          
                            //loop on methods arguments
                          ::naeem::hottentot::generator::ds::Argument *pArg;
                          for (int i = 0; i < pMethod->arguments_.size(); i++) {
                            pArg = pMethod->arguments_.at(i);
                            if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)){
                              serviceMethodsStr += pArg->type_ + " " + pArg->variable_;    
                            }else{
                              std::string argType =
                              ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(
                                pArg->type_);
                              serviceMethodsStr += argType + " " + pArg->variable_;
                            }
                            
                            if (i < pMethod->arguments_.size() - 1) {
                              serviceMethodsStr += ",";
                            }
                          }
                          serviceMethodsStr += ");\n";
};
replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_METHODS%]"), 19,
  serviceMethodsStr);


std::string path = outDir_ + "/" + pService->name_.c_str() + "Service.java";
::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceTmpStr);
}
}

void
JavaGenerator::GenerateServiceProxyBuilder(::naeem::hottentot::generator::ds::Module *pModule) {
  ::naeem::hottentot::generator::ds::Service *pService;
  std::string replacableServiceProxyBuilderTmpStr;
  for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.template
    std::string basePackageName = pModule->package_;
    pService = pModule->services_.at(i);
    std::string replacableServiceProxyBuilderTmpStr;
                        //write service proxy builder
    replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr;
    ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%INDENT%]" , indent_ , 1);
    ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
    ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
                        // while (replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableServiceProxyBuilderTmpStr.replace(
                        //             replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                        //             basePackageName);
                        // }
                        // while (replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                        //     replacableServiceProxyBuilderTmpStr.replace(
                        //             replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16, pService->name_);
                        // }

    std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxyBuilder.java";
    ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceProxyBuilderTmpStr);
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
    std::string serviceName = pService->name_;
    std::string lowerCaseServiceName = pService->name_;
    lowerCaseServiceName[0] += 32;
    replacableRequestHandlerTmpStr = requestHandlerTmpStr;

    ::naeem::hottentot::generator::common::StringHelper::Replace(replacableRequestHandlerTmpStr , "[%INDENT%]" , indent_ , 1);
    ::naeem::hottentot::generator::common::StringHelper::Replace(replacableRequestHandlerTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        // while (replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableRequestHandlerTmpStr.replace(
                        //             replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
                        // }
    ::naeem::hottentot::generator::common::StringHelper::Replace(replacableRequestHandlerTmpStr,"[%SERVICE_NAME%]" , pService->name_ , 1);
                        // while (replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                        //     replacableRequestHandlerTmpStr.replace(
                        //             replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16, pService->name_);
                        // }
    ::naeem::hottentot::generator::common::StringHelper::Replace(replacableRequestHandlerTmpStr,"[%SERVICE_NAME_LOWERCASE%]" , lowerCaseServiceName , 1);

    ::naeem::hottentot::generator::ds::Method *pMethod;
    std::string methodConditionStr;

    for (int i = 0; i < pService->methods_.size(); i++) {
      pMethod = pService->methods_.at(i);
      std::string lowerCaseReturnType = pMethod->returnType_;
      lowerCaseReturnType[0] += 32;
                            //get hashed mehod id
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
        indent_ + indent_ + indent_ + "Argument arg" + ssI.str() + " = args.get(" +
          ssI.str() + ");\n";
std::string argType = 
::naeem::hottentot::generator::common::TypeHelper::GetJavaType(
  pArg->type_);
std::string capitalizedArgVar = 
::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
  pArg->variable_);
methodConditionStr += indent_ + indent_ + indent_ +
"byte[] serialized"
+ capitalizedArgVar;
methodConditionStr += " = arg" + ssI.str() + ".getData();\n";
if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pArg->type_)){
  methodConditionStr +=
  indent_ + indent_ + indent_ +
  pArg->type_ + " " + pArg->variable_ +
  " = new " +
  pArg->type_ + "();\n";

  methodConditionStr +=
  indent_ + indent_ + indent_ + pArg->variable_ + ".deserialize(serialized" +
    pArg->type_ + ");\n";
}else{
  std::string javaType = 
  ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(
    pArg->type_);
  std::string capitalizedArgType = 
  ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
    pArg->type_);
  std::string capitalizedArgVar = 
  ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
    pArg->variable_);
  if(capitalizedArgType == "String"){
    capitalizedArgType = "FullString";
  }
  methodConditionStr +=
  indent_ + indent_ + indent_ +
  javaType +
  " " +
  pArg->variable_.c_str() +
  " = PDTDeserializer.get" +
  capitalizedArgType +
  "(serialized" + 
    capitalizedArgVar + 
    ");\n";
}
}
if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)){
 methodConditionStr +=
 indent_ + indent_ + indent_ + pMethod->returnType_ + " " + lowerCaseReturnType +
 " = null;\n"; 
}

methodConditionStr += indent_ + indent_ + indent_ + "Response response = new Response();\n";
                            //methodConditionStr += indent_ + indent_ + "try{\n";
if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)){
  methodConditionStr +=
  indent_ + indent_ + indent_ + lowerCaseReturnType + " = " + lowerCaseServiceName +
  "Impl." + pMethod->name_ + "(";
}else{
  std::string javaReturnType = 
  ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(
    pMethod->returnType_);
  methodConditionStr +=
  indent_ + indent_ + indent_ + javaReturnType +
  " result = " +
  lowerCaseServiceName +
  "Impl." + pMethod->name_ + "(";
}
for (int i = 0; i < pMethod->arguments_.size(); i++) {
  pArg = pMethod->arguments_.at(i);
  methodConditionStr += pArg->variable_;
  if (i < pMethod->arguments_.size() - 1) {
    methodConditionStr += pArg->variable_ += ",";
  }
}
methodConditionStr += ");\n";

if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)){

  methodConditionStr +=
  indent_ + indent_ + indent_ + "byte[] serialized" + pMethod->returnType_ + " = " +
  lowerCaseReturnType + ".serialize();\n";    
}else{
  std::string javaReturnType = 
  ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(
    pMethod->returnType_);
  std::string capitalizedReturnType = 
  ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
    pMethod->returnType_);
  methodConditionStr += 
  indent_ + indent_ + indent_ +
  "byte[] serializedResult = " + 
  "PDTSerializer.get" +
  capitalizedReturnType + 
  "( result );\n";
}


methodConditionStr += indent_ + indent_ + indent_ + "response.setStatusCode((byte) 100);\n";

if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pMethod->returnType_)){
  methodConditionStr +=
  indent_ + indent_ + indent_ + "response.setData(serialized" + pMethod->returnType_ +
    ");\n";
methodConditionStr += indent_ + indent_ + indent_ + "response.setLength(serialized" +
  pMethod->returnType_ + ".length + 1);\n";    
}else{
  methodConditionStr +=
  indent_ + indent_ + indent_ +
  "response.setData(serializedResult);\n";
  methodConditionStr += indent_ + indent_ + indent_ +
  "response.setLength(serializedResult.length + 1);\n";
}

methodConditionStr += indent_ + indent_ + indent_ + "return response;\n";
methodConditionStr += indent_ + indent_ + "}\n";

}
replacableRequestHandlerTmpStr.replace(
  replacableRequestHandlerTmpStr.find("[%METHOD_CONDITIONS%]"), 21,
  methodConditionStr);

std::string path = outDir_ + "/" + pService->name_.c_str() + "RequestHandler.java";
::naeem::hottentot::generator::common::Os::WriteFile(path , replacableRequestHandlerTmpStr);
}
}

void
JavaGenerator::GenerateServiceProxy(::naeem::hottentot::generator::ds::Module *pModule) {
  ::naeem::hottentot::generator::ds::Service *pService;
  std::string basePackageName = pModule->package_;
  for (int i = 0; i < pModule->services_.size(); i++) {
    std::string replacableServiceProxyStrTmp = serviceProxyTmpStr;
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
      pMethod = pService->methods_.at(i);
      std::string returnType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(pMethod->returnType_);
      methodsStr += "public " + returnType + " " + pMethod->name_ + "(";
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
  ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
    pArg->variable_);     
  if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pArg->type_)){
    methodsStr += indent_ + indent_ +
    "byte[] serialized" +
    capitalalizedArgVar + " = " +
    pArg->variable_ + ".serialize();\n";
  }else{
    std::string capitalizedArgType =
    ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
      pArg->type_);
    methodsStr += indent_ + indent_ +
    "byte[] serialized" +
    capitalalizedArgVar + " = " +
    "PDTSerializer.get" + 
    capitalizedArgType +
    "(" +
      pArg->variable_+ 
      ");\n" ;
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
  methodsStr += indent_ + indent_ + "Argument arg" + ssI.str() + " = new Argument();\n";
  methodsStr += indent_ + indent_ + "arg" + ssI.str() + ".setDataLength(";

    if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pArg->type_)){
      methodsStr += pArg->variable_ + ".serialize().length);\n";
methodsStr += indent_ + indent_ + 
"arg" + ssI.str() + ".setData(" + pArg->variable_.c_str() +
  ".serialize());\n";
}else{
  std::string capitalizedArgType = 
  ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
    pArg->type_); 
  methodsStr += "PDTSerializer.get" + 
  capitalizedArgType +
  "(" +
    pArg->variable_.c_str() +
    ").length);\n";
methodsStr += indent_ + indent_ + 
"arg" + ssI.str() + ".setData(PDTSerializer.get" + 
  capitalizedArgType + 
  "(" + 
    pArg->variable_ + 
    "));\n";
}

methodsStr += indent_ + indent_ + "request.addArgument(arg" + ssI.str() + ");\n";
}
                            //calculate request length
methodsStr += indent_ + indent_ + "int dataLength = 0;\n";
methodsStr += indent_ + indent_ + "//calculate data length for every argument\n";
for (int i = 0; i < pMethod->arguments_.size(); i++) {
  pArg = pMethod->arguments_.at(i);
  std::string argDataLengthVarName = pArg->variable_ + "DataLength";
  std::string capitalizedArgVar = 
  ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
    pArg->variable_); 
  std::string argDataLengthByteArrayLengthVarName =
  pArg->variable_ + "DataLengthByteArrayLength";
  methodsStr += indent_ + indent_ + "//calulate " + argDataLengthVarName + "\n";
  methodsStr += indent_ + indent_ + "int " + argDataLengthVarName + "= serialized" +
  capitalizedArgVar  + ".length;\n";
  methodsStr +=
  indent_ + indent_ + "int " + argDataLengthByteArrayLengthVarName + " = 1;\n";
  methodsStr += indent_ + indent_ + "if (" + argDataLengthVarName + " >= 0x80) {\n";
  methodsStr +=
  indent_ + indent_ + indent_ + "if (" + argDataLengthVarName + " <= 0xff) {\n";
  methodsStr += indent_ + indent_ + indent_ + indent_ + "//ex 0x81 0xff\n";
  methodsStr += indent_ + indent_ + indent_ + indent_ + "" +
  argDataLengthByteArrayLengthVarName + " = 2;\n";
  methodsStr += indent_ + indent_ + indent_ + "} else if (" + argDataLengthVarName +
    " <= 0xffff) {\n";
methodsStr += indent_ + indent_ + indent_ + indent_ + "//ex 0x82 0xff 0xff\n";
methodsStr += indent_ + indent_ + indent_ + indent_ + "" +
argDataLengthByteArrayLengthVarName + " = 3;\n";
methodsStr += indent_ + indent_ + indent_ + "} else if (" + argDataLengthVarName +
  " <= 0xffffff) {\n";
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
methodsStr += indent_ + indent_ + "//deserialize " + pMethod->returnType_ +
"part from response\n";
std::string lowerCaseReturnType = pMethod->returnType_;
std::string capitalizedReturnType = 
::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
  pMethod->returnType_);
lowerCaseReturnType[0] += 32;
if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pArg->type_)) {
  methodsStr += indent_ + indent_ + "" + pMethod->returnType_ + " " + lowerCaseReturnType +
  "= null;\n";    
}
methodsStr += indent_ + indent_ + "if (response.getStatusCode() == -1) {\n";
methodsStr += indent_ + indent_ + indent_ + "// TODO\n";
methodsStr += indent_ + indent_ + "}\n";

if(::naeem::hottentot::generator::common::TypeHelper::IsUDT(pArg->type_)) {
  methodsStr += indent_ + indent_ + indent_ + "" + lowerCaseReturnType + "= new " +
  pMethod->returnType_ + "();\n";
  methodsStr += indent_ + indent_ + indent_ + "" + lowerCaseReturnType +
  ".deserialize(response.getData());\n";
  methodsStr += indent_ + indent_ + "return " + lowerCaseReturnType + ";\n";
  methodsStr += indent_ + "}\n"; 
}else {
  std::string capitalizedArgType = 
  ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(
    pArg->type_);
  methodsStr += indent_ + indent_ +
  "return PDTDeserializer.get" + 
  capitalizedReturnType + 
  "(response.getData());\n";
  methodsStr += indent_ + "}\n"; 
}
}
replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%METHODS%]"), 11,
 methodsStr);
std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxy.java";
::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceProxyStrTmp);
}
}
}
}
}
}
