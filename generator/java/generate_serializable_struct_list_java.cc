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
        JavaGenerator::GenerateSerializableStructList(::naeem::hottentot::generator::ds::Module *pModule) {
          for (int i = 0; i < pModule->structs_.size(); i++) {
            ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(i);
            std::string basePackageName = pModule->package_;
            std::string replacableStructTmpStr = structTmpStr_;
            std::string lowerCaseStructName = ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(pStruct->name_);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableSerializableStructListTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableSerializableStructListTmpStr , "[%INDENT%]" , indent_ , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableSerializableStructListTmpStr , "[%STRUCT_NAME%]" , pStruct->name_ , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableSerializableStructListTmpStr , "[%LOWER_CASE_STRUCT_NAME%]" , lowerCaseStructName , 1);            
            std::string path = outDir_ + "/" + pStruct->name_.c_str() + ".java";
            ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableStructTmpStr);
          }
        }

      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM