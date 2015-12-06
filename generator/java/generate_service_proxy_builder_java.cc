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
        JavaGenerator::GenerateServiceProxyBuilder(::naeem::hottentot::generator::ds::Module *pModule) {
          ::naeem::hottentot::generator::ds::Service *pService;
          std::string replacableServiceProxyBuilderTmpStr;
          for (int i = 0; i < pModule->services_.size(); i++) {
            //write abstractService.template
            std::string basePackageName = pModule->package_;
            pService = pModule->services_.at(i);
            std::string replacableServiceProxyBuilderTmpStr;
            //write service proxy builder
            replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr_;
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%INDENT%]" , indent_ , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
            std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxyBuilder.java";
            ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceProxyBuilderTmpStr);
          }
        }

      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM