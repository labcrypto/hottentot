#include <sys/stat.h>
#include <sstream>
#include "java_generator.h"
#include "../ds/hot.h"
#include "../common/os.h" 

namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
        void
        JavaGenerator::GenerateServerImpls(::naeem::hottentot::generator::ds::Module *pModule) {
          std::string basePackageName = pModule->package_;
          ::naeem::hottentot::generator::ds::Service *pService;
          for (int i = 0; i < pModule->services_.size(); i++) {
            std::string replacableServerImplTmpStr = serverImplTmpStr_;  
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServerImplTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServerImplTmpStr , "[%INDENT%]" , indent_ , 1);
            pService = pModule->services_.at(i);
            std::string serviceName = pService->GetName();
            std::string methodsStr = "";
            ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServerImplTmpStr ,
                                                                      "[%SERVICE_NAME%]" , 
                                                                      serviceName , 1);
            std::string path = serverOutDir_ + "/" + serviceName + "Impl.java";
            ::naeem::hottentot::generator::common::Os::WriteFile(path , 
                                                            replacableServerImplTmpStr);
          }          
        }
      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM#include <sys/stat.h>