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
  JavaGenerator::GenerateAbstractService (
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    ::naeem::hottentot::generator::ds::Service *pService;
    std::string replacableAbstractServiceTmpStr;
    for (int i = 0; i < pModule->services_.size(); i++) {
      std::string basePackageName = pModule->package_;
      pService = pModule->services_.at(i);
      std::string path = outDir_ + "/Abstract" + pService->name_.c_str() + "Service.java";
      os.open(path.c_str(), std::ios::trunc);
      replacableAbstractServiceTmpStr = abstractServiceTmpStr_;
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableAbstractServiceTmpStr , "[%INDENT%]", 
        indent_, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableAbstractServiceTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableAbstractServiceTmpStr, 
        "[%SERVICE_NAME%]", 
        pService->name_, 
        1
      );
      std::stringstream ssID;
      ssID << pService->GetHash();
      replacableAbstractServiceTmpStr.replace (
        replacableAbstractServiceTmpStr.find("[%SERVICE_ID%]"), 14, ssID.str()
      );
      os.write (
        replacableAbstractServiceTmpStr.c_str(), 
        replacableAbstractServiceTmpStr.size()
      );
      os.close();
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org