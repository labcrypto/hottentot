#include <sys/stat.h>
#include <sstream>
#include "java_generator.h"
#include "../ds/hot.h"
#include "../common/string_helper.h"
#include "../common/os.h" 
#include "../common/type_helper.h" 
#include <map>
#include <sstream>


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
        void
        JavaGenerator::GenerateEnums(::naeem::hottentot::generator::ds::Module *pModule) {
          //loop on methods
          // for (int i = 0; i < pMadule->services_.size(); i++) {
          //   for(int j = 0 ; j < pModule->services_.at(i)->methods_.size() ; j++){
          //     ::naeem::hottentot::generator::ds::Method* pMethod = pModule->services_.at(i)->methods_.at(j);

          //   }
          // }

          //TODO make struct for PDT arg and return type in methods
          //loop on structs in everey module
          for (int i = 0; i < pModule->enums_.size(); i++) {
            ::naeem::hottentot::generator::ds::Enum *pEnum = pModule->enums_.at(i);
            std::string basePackageName = pModule->package_;
            std::string replacableEnumTmpStr = enumTmpStr_;
            ::naeem::hottentot::generator::Context.enums_.push_back(pEnum);
            std::map<uint16_t, std::string>::iterator it;
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableEnumTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableEnumTmpStr , "[%INDENT%]" , indent_ , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableEnumTmpStr , "[%ENUM_NAME%]" , pEnum->GetName() , 1);
            std::string membersStr = "";
            uint8_t mapCounter = 1;
            for (std::map<uint16_t, std::string>::iterator it 
             = pEnum->revItems_.begin();
             it != pEnum->revItems_.end();
             ++it) {
              std::string itemName = it->second;
              uint16_t itemValue = it->first;
              std::stringstream itemValueStr;
              itemValueStr << itemValue;
              membersStr += indent_ +  itemName + "((short) " + itemValueStr.str() +  ")";
              if(mapCounter != pEnum->revItems_.size()){
                membersStr += ",\n";
              }else {
                membersStr += ";";
              }
              mapCounter++;
            }
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableEnumTmpStr , "[%MEMBERS%]" , membersStr , 1);            std::string path = outDir_ + "/" + pEnum->GetName().c_str() + ".java";
            ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableEnumTmpStr);
          }
        }

      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM