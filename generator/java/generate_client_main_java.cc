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
        JavaGenerator::GenerateClientMain(::naeem::hottentot::generator::ds::Module *pModule) {
          std::string basePackageName = pModule->package_;
          std::string replacableClientMainTmpStr = clientMainTmpStr_;
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableClientMainTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableClientMainTmpStr , "[%INDENT%]" , indent_ , 1);
          std::string importProxiesStr = "";
          std::string allProxiesStr = "";
          ::naeem::hottentot::generator::ds::Service *pService;
          for (int i = 0; i < pModule->services_.size(); i++) {
            pService = pModule->services_.at(i);
            std::string serviceName = pService->GetName();
            importProxiesStr += "import " + basePackageName + ".hotgen." +
                                serviceName +  "Service;\n";
            importProxiesStr += "import " + basePackageName + ".hotgen." +
                                serviceName  + "ServiceProxyBuilder;\n";
            allProxiesStr += "final " + serviceName + "Service proxy = " + 
                              serviceName + "ServiceProxyBuilder.create(\"127.0.0.1\", 2000);\n";
          }
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableClientMainTmpStr ,
                                                                      "[%ALL_PROXIES%]" , 
                                                                      allProxiesStr , 1);
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableClientMainTmpStr ,
                                                                      "[%IMPORT_PROXIES%]" , 
                                                                      importProxiesStr , 1);
          std::string path = clientOutDir_ + "/Main.java";
          ::naeem::hottentot::generator::common::Os::WriteFile(path , 
                                                              replacableClientMainTmpStr);
        }
      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM