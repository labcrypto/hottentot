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
  JavaGenerator::GenerateServiceProxyBuilder (
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    ::naeem::hottentot::generator::ds::Service *pService;
    std::string replacableServiceProxyBuilderTmpStr;
    for (int i = 0; i < pModule->services_.size(); i++) {
      std::string basePackageName = pModule->package_;
      pService = pModule->services_.at(i);
      std::string replacableServiceProxyBuilderTmpStr;
      replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr_;
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServiceProxyBuilderTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServiceProxyBuilderTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName,
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableServiceProxyBuilderTmpStr, 
        "[%SERVICE_NAME%]", 
        pService->name_, 
        1
      );
      std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxyBuilder.java";
      ::naeem::hottentot::generator::common::Os::WriteFile (
        path, 
        replacableServiceProxyBuilderTmpStr
      );
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org