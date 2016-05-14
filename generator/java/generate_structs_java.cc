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
  JavaGenerator::GenerateStructs (
    ::org::labcrypto::hottentot::generator::Module *pModule
  ) {
    //TODO make struct for PDT arg and return type in methods
    for (int i = 0; i < pModule->structs_.size(); i++) {
      ::org::labcrypto::hottentot::generator::Struct *pStruct = pModule->structs_.at(i);
      std::string basePackageName = pModule->package_;
      std::string replacableStructTmpStr = structTmpStr_;
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableStructTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName + (extendModule_.size() > 0 ? "." : "") + extendModule_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableStructTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::org::labcrypto::hottentot::generator::StringHelper::Replace (
        replacableStructTmpStr, 
        "[%STRUCT_NAME%]", 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstCapital (
          pStruct->GetName()
        ), 
        1
      );
      std::string declarationStr;
      std::string getterSetterStr;
      std::string declarationJavaType;
      std::string capitalizedDeclarationJavaType;
      for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
        ::org::labcrypto::hottentot::generator::Declaration *declarationPtr = it->second;
        declarationJavaType = 
          ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(declarationPtr->type_);              
        capitalizedDeclarationJavaType  = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationJavaType);
        std::string declarationName = declarationPtr->variable_;
        std::string capitalizedDeclarationName = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital (
            declarationPtr->variable_
          );
        if (declarationJavaType.compare("String") == 0) {
          declarationStr += indent_ + "private " + declarationJavaType +
                            " " + declarationName + " = \"\";\n";  
        } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(declarationPtr->type_)) {
            std::string fetchedListType = 
              ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(declarationPtr->type_);
            declarationStr += indent_ + "private " + declarationJavaType +
                              " " + declarationName + " = new Array" + 
                              declarationJavaType +"();\n";   
        } else {
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
      std::string toStringMethodStr = indent_  + "@Override \n"; 
      toStringMethodStr += indent_  + "public String toString() { \n"; 
      toStringMethodStr += indent_ + indent_ + "return \"" + pStruct->name_.c_str() + "{\" + \n";
      int counter = 0;
      for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
        ::org::labcrypto::hottentot::generator::Declaration *pDeclaration = it->second;
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
      replacableStructTmpStr.replace (
        replacableStructTmpStr.find("[%MEMBERS%]"),
        11,
        declarationStr + getterSetterStr + toStringMethodStr
      );
      std::string serializeMethodStr;
      int declarationCounter = 0;
      for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
            declarationCounter++;
            std::stringstream declarationCounterStr;
            declarationCounterStr << declarationCounter;
            ::org::labcrypto::hottentot::generator::Declaration *declarationPtr = it->second;
            std::string capitalizedDeclarationName = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationPtr->variable_);
            if (::org::labcrypto::hottentot::generator::TypeHelper::IsEnum(declarationPtr->type_)) {
               serializeMethodStr += indent_ + indent_ + 
                                    "byte[] serialized" + capitalizedDeclarationName + " = " +
                                    declarationPtr->variable_ + ".serialize();\n";
            } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(declarationPtr->type_)) {
              std::string fetchedListType = 
                ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(declarationPtr->type_);
              std::string capitalizedFetchedListType = 
                ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(fetchedListType);
              std::string serializableVar =
                "serializable" + capitalizedFetchedListType + 
                  "List" + declarationCounterStr.str();
              serializeMethodStr += indent_ + indent_+
                "Serializable" + capitalizedFetchedListType +
                  "List " + serializableVar + " = new Serializable" + capitalizedFetchedListType +
                    "List();\n";
              
              serializeMethodStr += indent_ + indent_ + 
                serializableVar + ".set" + capitalizedFetchedListType + "List(" + 
                  declarationPtr->variable_.c_str() + ");\n"; 
              
              serializeMethodStr += indent_ + indent_ + 
                "byte[] serialized" + capitalizedDeclarationName + " " + 
                  " = " + serializableVar + ".serializeWithLength();\n";
            } else if (declarationPtr->type_.compare("data") == 0) {
              serializeMethodStr += indent_ + indent_ + "byte[] serialized" + 
                capitalizedDeclarationName + " = PDTSerializer.getData(" + 
                  declarationPtr->variable_ + ");\n";
            }else{
              serializeMethodStr += indent_ + indent_ + "byte[] serialized" + 
                capitalizedDeclarationName + " = PDTSerializer.get";
              declarationJavaType = 
                ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(declarationPtr->type_);
              capitalizedDeclarationJavaType = 
                ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationJavaType);
              if(declarationPtr->type_[0] == 'u'){
                ::org::labcrypto::hottentot::generator::StringHelper::Replace (
                  declarationPtr->type_ ,
                  "u" ,
                  "" ,
                  1
                );
              }
              std::string capitalizedDeclarationType  = 
                ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationPtr->type_);
              serializeMethodStr += capitalizedDeclarationType + "(";
              serializeMethodStr += declarationPtr->variable_ + ");\n";
            }
      }
      serializeMethodStr += indent_ + indent_ + "byte[] output = new byte[";
      for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
            ::org::labcrypto::hottentot::generator::Declaration *declarationPtr = it->second;
            std::string capitalizedDeclarationName = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationPtr->variable_.c_str());
            serializeMethodStr += "serialized" + capitalizedDeclarationName + ".length";
            if (it == (--(pStruct->declarations_.end()))) {
              serializeMethodStr += "];\n";
            }else {
              serializeMethodStr += " + ";
            }
      }
      serializeMethodStr += indent_ + indent_ + "int counter = 0;\n";
      serializeMethodStr += indent_ + indent_ + "//use a loop for every property\n";
      for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
        ::org::labcrypto::hottentot::generator::Declaration *declarationPtr = it->second;
        declarationJavaType = 
          ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(declarationPtr->type_);
        capitalizedDeclarationJavaType = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationJavaType);
        std::string capitalizedDeclarationName = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationPtr->variable_);
        serializeMethodStr += indent_ + indent_ + "for (int i = 0; i < serialized" +
          capitalizedDeclarationName + ".length; i++) {\n";
        serializeMethodStr += indent_ + indent_ + indent_ + "output[counter++] = serialized" +
        capitalizedDeclarationName + "[i];\n";
        serializeMethodStr += indent_ + indent_ + "}\n";
      }
      serializeMethodStr += indent_ + indent_ + "return output;"; 
      replacableStructTmpStr.replace (
        replacableStructTmpStr.find("[%SERIALIZE_METHOD_BODY%]"), 
        25, 
        serializeMethodStr
      );
      declarationCounter = 0;
      std::string deserializeMethodStr;
      deserializeMethodStr += indent_ + indent_ + indent_ +  "int counter = 0;\n";
      deserializeMethodStr += indent_ + indent_ + indent_ + "int dataLength = 0;\n";
      deserializeMethodStr += indent_ + indent_ + indent_ + "int numbersOfBytesForDataLength;\n";
      deserializeMethodStr += indent_ + indent_ + indent_ + "//do for every property\n";
      for (std::map<uint32_t, ::org::labcrypto::hottentot::generator::Declaration*>::iterator it 
             = pStruct->declarations_.begin();
           it != pStruct->declarations_.end();
           ++it) {
          ::org::labcrypto::hottentot::generator::Declaration *declarationPtr = it->second;
          declarationJavaType = 
            ::org::labcrypto::hottentot::generator::TypeHelper::GetJavaType(declarationPtr->type_);
          std::string capitalizedDeclarationType = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationPtr->type_);
          std::string capitalizedDeclarationName = 
            ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationPtr->variable_);
          deserializeMethodStr += indent_ + indent_ + "//" + declarationPtr->variable_ + " : " + declarationJavaType + "\n";
          if (declarationPtr->type_.compare("string") == 0 ||
              declarationPtr->type_.compare("data") == 0 || 
              ::org::labcrypto::hottentot::generator::TypeHelper::IsListType(declarationPtr->type_)) {
                deserializeMethodStr += indent_ + indent_ + "dataLength = 0;\n";
                deserializeMethodStr += indent_ + indent_ +
                "if (( serializedByteArray[counter] & 0x80) == 0 ) {\n";
                deserializeMethodStr += indent_ + indent_ + indent_ + 
                  "dataLength = serializedByteArray[counter++];\n";
                deserializeMethodStr += indent_ + indent_ + "} else {\n";  
                deserializeMethodStr += indent_ + indent_ + indent_ + 
                  "numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;\n";
                deserializeMethodStr += indent_ + indent_ + indent_ + 
                  "byte[] serializedByteArrayLength = new byte[numbersOfBytesForDataLength];\n";
                deserializeMethodStr += indent_ + indent_ + indent_ + 
                  "for (byte i = 0; i < numbersOfBytesForDataLength; i++) {\n";
                deserializeMethodStr += indent_ + indent_ + indent_ + indent_ + 
                  "serializedByteArrayLength[i] = serializedByteArray[counter++];\n";
                deserializeMethodStr += indent_ + indent_ + indent_ + "}\n";
                deserializeMethodStr += indent_ + indent_ + indent_ + 
                  "dataLength = ByteArrayToInteger.getInt(serializedByteArrayLength);\n";
                deserializeMethodStr += indent_ + indent_ + "}\n";
                deserializeMethodStr += indent_ + indent_ + 
                  "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[dataLength];\n";
                deserializeMethodStr += indent_ + indent_ + 
                  "System.arraycopy(serializedByteArray,counter," + declarationPtr->variable_.c_str() + 
                    "ByteArray,0,dataLength);\n";
                deserializeMethodStr += indent_ + indent_ + "counter += dataLength;\n";
                if (declarationPtr->type_.compare("string") == 0 ) {
                  deserializeMethodStr += indent_ + indent_ + "set" + 
                    capitalizedDeclarationName + "(PDTDeserializer.get" + 
                      capitalizedDeclarationType + "(" + declarationPtr->variable_.c_str() + 
                        "ByteArray));\n";
                } else if (declarationPtr->type_.compare("string") == 0 ) {
                  deserializeMethodStr += indent_ + indent_ + "set" + 
                    capitalizedDeclarationName + "(" + declarationPtr->variable_.c_str() + 
                      "ByteArray);\n";
                } else if (::org::labcrypto::hottentot::generator::TypeHelper::IsListType(declarationPtr->type_)) {
                  std::string fetchedListType = 
                    ::org::labcrypto::hottentot::generator::TypeHelper::FetchTypeOfList(declarationPtr->type_);                        
                  std::string upperCaseListType = 
                    ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(fetchedListType);
                  declarationCounter++;
                  std::stringstream declarationCounterStr;
                  declarationCounterStr << declarationCounter;
                  std::string serializableVar = 
                    "serializable" + upperCaseListType +
                      "List" + declarationCounterStr.str(); 
                  deserializeMethodStr += indent_ + indent_ + 
                    "Serializable" + upperCaseListType + "List " + 
                      serializableVar + " = new Serializable" + 
                        upperCaseListType + "List();\n";
                  deserializeMethodStr += indent_ + indent_ + 
                    serializableVar +  ".deserialize(" +
                      declarationPtr->variable_.c_str() + "ByteArray);\n";
                  deserializeMethodStr += indent_ + indent_ + 
                    "set" + capitalizedDeclarationName + "(" + 
                      serializableVar + ".get" + upperCaseListType +
                        "List());\n";
                }
          } else {
            uint32_t dataLength = 
              ::org::labcrypto::hottentot::generator::TypeHelper::GetTypeLength(declarationPtr->type_.c_str());
            capitalizedDeclarationJavaType = 
              ::org::labcrypto::hottentot::generator::StringHelper::MakeFirstCapital(declarationJavaType);
            std::stringstream dataLengthStr;
            dataLengthStr << dataLength;
            deserializeMethodStr += indent_ + indent_ + "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[" + dataLengthStr.str() + "];\n";
            deserializeMethodStr += indent_ + indent_ + "for(int i = 0 ; i < " + dataLengthStr.str() + " ; i++){\n";
            deserializeMethodStr += indent_ + indent_ + indent_ + declarationPtr->variable_.c_str() + "ByteArray[i] = serializedByteArray[counter++];\n";            
            deserializeMethodStr += indent_ + indent_ + "}\n";
            if (::org::labcrypto::hottentot::generator::TypeHelper::IsEnum(declarationPtr->type_)) {
              deserializeMethodStr += indent_ + indent_ + 
                                      "set" + capitalizedDeclarationName + "(" + 
                                      declarationPtr->type_ + ".deserialize(" + 
                                      declarationPtr->variable_ + "ByteArray));\n";
            } else {
              deserializeMethodStr += indent_ + indent_ +
                                      "set" + capitalizedDeclarationName + 
                                      "(PDTDeserializer.get" + capitalizedDeclarationType + "(" +
                                       declarationPtr->variable_.c_str() + "ByteArray));\n";  
            }
          }
      }
      replacableStructTmpStr.replace (
        replacableStructTmpStr.find("[%DESERIALIZE_METHOD_BODY%]"), 
        27, 
        deserializeMethodStr
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
        ::org::labcrypto::hottentot::generator::StringHelper::MakeCamelCaseFirstCapital (
          pStruct->GetName()
        ) + ".java";
      ::org::labcrypto::hottentot::generator::Os::WriteFile(path , replacableStructTmpStr);
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org