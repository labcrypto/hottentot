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
        JavaGenerator::GenerateAbstractService(::naeem::hottentot::generator::ds::Module *pModule) {
          ::naeem::hottentot::generator::ds::Service *pService;
          std::string replacableAbstractServiceTmpStr;
          //loop for every services
          for (int i = 0; i < pModule->services_.size(); i++) {
            //write abstractService.template
            std::string basePackageName = pModule->package_;
            pService = pModule->services_.at(i);
            std::string path = outDir_ + "/Abstract" + pService->name_.c_str() + "Service.java";
            os.open(path.c_str(), std::ios::trunc);
            replacableAbstractServiceTmpStr = abstractServiceTmpStr_;
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%INDENT%]" , indent_ , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
            //get service ID from hot parser
            std::stringstream ssID;
            ssID << pService->GetHash();
            replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_ID%]"), 14, ssID.str());
            os.write(replacableAbstractServiceTmpStr.c_str(), replacableAbstractServiceTmpStr.size());
            os.close();
          }
        }
      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM