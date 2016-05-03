#include <sys/stat.h>

#include <sstream>

#include "java_generator.h"

#include "../hot.h"
#include "../os.h" 


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  void
  JavaGenerator::GenerateServerImpls (
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    std::string basePackageName = pModule->package_;
    ::naeem::hottentot::generator::ds::Service *pService;
    for (int i = 0; i < pModule->services_.size(); i++) {
      std::string replacableServerImplTmpStr = serverImplTmpStr_;  
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServerImplTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServerImplTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      pService = pModule->services_.at(i);
      std::string serviceName = pService->GetName();
      std::string methodsStr = "";
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServerImplTmpStr,
        "[%SERVICE_NAME%]", 
        serviceName, 
        1
      );
      std::string path = serverOutDir_ + "/" + serviceName + "Impl.java";
      ::naeem::hottentot::generator::common::Os::WriteFile (
        path, 
        replacableServerImplTmpStr
      );
    }          
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org