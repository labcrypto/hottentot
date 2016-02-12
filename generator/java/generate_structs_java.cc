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
        JavaGenerator::GenerateStructs(::naeem::hottentot::generator::ds::Module *pModule) {
          //loop on methods
          // for (int i = 0; i < pMadule->services_.size(); i++) {
          //   for(int j = 0 ; j < pModule->services_.at(i)->methods_.size() ; j++){
          //     ::naeem::hottentot::generator::ds::Method* pMethod = pModule->services_.at(i)->methods_.at(j);

          //   }
          // }

          //TODO make struct for PDT arg and return type in methods
          //loop on structs in everey module
          for (int i = 0; i < pModule->structs_.size(); i++) {
            ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(i);
            std::string basePackageName = pModule->package_;
            std::string replacableStructTmpStr = structTmpStr_;
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%INDENT%]" , indent_ , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%STRUCT_NAME%]" , pStruct->name_ , 1);
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
              if(declarationJavaType.compare("String") == 0){
                declarationStr += indent_ + "private " + declarationJavaType +
                                  " " + declarationName + " = \"\";\n";  
              }else{
                declarationStr += indent_ + "private " + declarationJavaType +
                                  " " + declarationName + ";\n";  
              }
              
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


             // @Override
             //  public String toString() {
             //    return "UserHot{" +
             //            "username='" + username + '\'' +
             //            ", password='" + password + '\'' +
             //            ", email='" + email + '\'' +
             //            '}';
             //  }

            //toString method
            std::string toStringMethodStr = indent_  + "@Override \n"; 
            toStringMethodStr += indent_  + "public String toString() { \n"; 
            toStringMethodStr += indent_ + indent_ + "return \"" + pStruct->name_.c_str() + "{\" + \n";
            int counter = 0;
            for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
             it != pStruct->declarations_.end();
             ++it) {
              ::naeem::hottentot::generator::ds::Declaration *pDeclaration = it->second;
              toStringMethodStr += indent_ + indent_ + indent_ + "\"";
              if(counter != 0){
                toStringMethodStr += ",";
              }
              counter++;
              toStringMethodStr += pDeclaration->variable_ + " = '\" + " +
                                   pDeclaration->variable_.c_str() + " + '\\'' + \n"; 
            }
            toStringMethodStr += indent_ + indent_ + indent_ + "\"}\"; \n";
            toStringMethodStr += indent_ + "}\n";


            replacableStructTmpStr.replace(replacableStructTmpStr.find("[%MEMBERS%]"),
                                          11,
                                          declarationStr + getterSetterStr + toStringMethodStr);
            //serilize method
            std::string serializeMethodStr;
            for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
                = pStruct->declarations_.begin();
                it != pStruct->declarations_.end();
                ++it) {
                  ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
                  std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->variable_);
                  if(::naeem::hottentot::generator::common::TypeHelper::IsEnum(declarationPtr->type_)) {
                     serializeMethodStr += indent_ + indent_ + 
                                          "byte[] serialized" + capitalizedDeclarationName + " = " +
                                          declarationPtr->variable_ + ".serialize();\n";
                  }else if(declarationPtr->type_.compare("data") == 0){
                    serializeMethodStr += indent_ + indent_ + "byte[] serialized" + capitalizedDeclarationName + " = PDTSerializer.getData(" + declarationPtr->variable_ + ");\n";
                  }else{
                    //std::cout << "OKK";
                    serializeMethodStr += indent_ + indent_ + "byte[] serialized" + capitalizedDeclarationName + " = PDTSerializer.get";
                    declarationJavaType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(declarationPtr->type_);
                    capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationJavaType);
                    if(declarationPtr->type_[0] == 'u'){
                      ::naeem::hottentot::generator::common::StringHelper::Replace(declarationPtr->type_ ,
                                                                                   "u" ,
                                                                                   "" ,
                                                                                    1);
                    }
                    std::string capitalizedDeclarationType  = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->type_);
                    serializeMethodStr += capitalizedDeclarationType + "(";
                    serializeMethodStr += declarationPtr->variable_ + ");\n";
                  }
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
                  }else {
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
            replacableStructTmpStr.replace(replacableStructTmpStr.find("[%SERIALIZE_METHOD_BODY%]"), 25, serializeMethodStr);
            //deserialize method
            std::string deserializeMethodStr;
            deserializeMethodStr += indent_ + indent_ + indent_ +  "int counter = 0;\n";
            deserializeMethodStr += indent_ + indent_ + indent_ + "int dataLength = 0;\n";
            deserializeMethodStr += indent_ + indent_ + indent_ + "int numbersOfBytesForDataLength;\n";
            deserializeMethodStr += indent_ + indent_ + indent_ + "//do for every property\n";
            for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
             it != pStruct->declarations_.end();
             ++it) {
                ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
                declarationJavaType = ::naeem::hottentot::generator::common::TypeHelper::GetJavaType(declarationPtr->type_);
                std::string capitalizedDeclarationType = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->type_);
                std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationPtr->variable_);
                deserializeMethodStr += indent_ + indent_ + "//" + declarationPtr->variable_ + " : " + declarationJavaType + "\n";
                if(declarationJavaType.compare("String") == 0 ||
                   declarationJavaType.compare("byte[]") == 0) {
                  deserializeMethodStr += indent_ + indent_ + "dataLength = 0;\n";
                  deserializeMethodStr += indent_ + indent_ +
                  "if(( serializedByteArray[counter] & 0x80) == 0 ) {\n";
                  deserializeMethodStr += indent_ + indent_ + indent_ + "dataLength = serializedByteArray[counter++];\n";
                  deserializeMethodStr += indent_ + indent_ + "}else{\n";  
                  deserializeMethodStr += indent_ + indent_ + indent_ + "numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;\n";
                  deserializeMethodStr += indent_ + indent_ + indent_ + "byte[] serializedByteArrayLength = new byte[numbersOfBytesForDataLength];\n";
                  deserializeMethodStr += indent_ + indent_ + indent_ + "for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){\n";
                  deserializeMethodStr += indent_ + indent_ + indent_ + indent_ + "serializedByteArrayLength[i] = serializedByteArray[counter++];\n";
                  deserializeMethodStr += indent_ + indent_ + indent_ + "}\n";
                  deserializeMethodStr += indent_ + indent_ + indent_ + "dataLength = ByteArrayToInteger.getInt(serializedByteArrayLength);\n";
                  deserializeMethodStr += indent_ + indent_ + "}\n";
                  deserializeMethodStr += indent_ + indent_ + "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[dataLength];\n";
                  deserializeMethodStr += indent_ + indent_ + "System.arraycopy(serializedByteArray,counter," + declarationPtr->variable_.c_str() + "ByteArray,0,dataLength);\n";
                  deserializeMethodStr += indent_ + indent_ + "counter += dataLength;\n";
                  if(declarationJavaType.compare("String") == 0){
                    deserializeMethodStr += indent_ + indent_ + "set" + capitalizedDeclarationName + "(PDTDeserializer.get" + capitalizedDeclarationType + "(" + declarationPtr->variable_.c_str() + "ByteArray));\n";
                  }else if(declarationJavaType.compare("byte[]") == 0){
                    deserializeMethodStr += indent_ + indent_ + "set" + capitalizedDeclarationName + "(" + declarationPtr->variable_.c_str() + "ByteArray);\n";
                  }
                }else {
                  uint32_t dataLength = ::naeem::hottentot::generator::common::TypeHelper::GetTypeLength(declarationPtr->type_.c_str());
                  capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeFirstCapital(declarationJavaType);
                  std::stringstream dataLengthStr;
                  dataLengthStr << dataLength;
                  deserializeMethodStr += indent_ + indent_ + "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[" + dataLengthStr.str() + "];\n";
                  deserializeMethodStr += indent_ + indent_ + "for(int i = 0 ; i < " + dataLengthStr.str() + " ; i++){\n";
                  deserializeMethodStr += indent_ + indent_ + indent_ + declarationPtr->variable_.c_str() + "ByteArray[i] = serializedByteArray[counter++];\n";            
                  deserializeMethodStr += indent_ + indent_ + "}\n";
                  if(::naeem::hottentot::generator::common::TypeHelper::IsEnum(declarationPtr->type_)) {
                    deserializeMethodStr += indent_ + indent_ + 
                                            "set" + capitalizedDeclarationName + "(" + 
                                            declarationPtr->type_ + ".deserialize(" + 
                                            declarationPtr->variable_ + "ByteArray));\n";
                  }else {
                    deserializeMethodStr += indent_ + indent_ +
                                            "set" + capitalizedDeclarationName + 
                                            "(PDTDeserializer.get" + capitalizedDeclarationType + "(" +
                                             declarationPtr->variable_.c_str() + "ByteArray));\n";  
                  }
                }
            }
            replacableStructTmpStr.replace(replacableStructTmpStr.find("[%DESERIALIZE_METHOD_BODY%]"), 27, deserializeMethodStr);
            std::string path = outDir_ + "/" + pStruct->name_.c_str() + ".java";
            ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableStructTmpStr);
          }
        }

      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM