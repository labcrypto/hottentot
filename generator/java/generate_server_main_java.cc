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
  JavaGenerator::GenerateServerMain (
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    std::string basePackageName = pModule->package_;
    std::string replacableServerMainTmpStr = serverMainTmpStr_;
    ::naeem::hottentot::generator::common::StringHelper::Replace (
      replacableServerMainTmpStr, 
      "[%BASE_PACKAGE_NAME%]", 
      basePackageName, 
      1
    );
    ::naeem::hottentot::generator::common::StringHelper::Replace (
      replacableServerMainTmpStr, 
      "[%INDENT%]", 
      indent_, 
      1
    );
    ::naeem::hottentot::generator::ds::Service *pService;
    std::string registerServicesStr = "";
    for (int i = 0; i < pModule->services_.size(); i++) {
      pService = pModule->services_.at(i);
      std::string serviceName = pService->GetName();
      std::string lowerCaseServiceName = 
        ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(serviceName);
      registerServicesStr += indent_ + indent_ + "Service " + lowerCaseServiceName + "Service = new " +
                             serviceName + "Impl();\n";
      registerServicesStr += indent_ + indent_ + "serviceRuntime.register(\"127.0.0.1\",8080, " + 
                             lowerCaseServiceName + "Service);\n";              
    }          
    ::naeem::hottentot::generator::common::StringHelper::Replace (
      replacableServerMainTmpStr,
      "[%REGISTER_SERVICES%]", 
      registerServicesStr, 
      1
    );
    std::string path = serverOutDir_ + "/Main.java";
    ::naeem::hottentot::generator::common::Os::WriteFile (
      path, 
      replacableServerMainTmpStr
    );
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org