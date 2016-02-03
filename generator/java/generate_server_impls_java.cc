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
        JavaGenerator::GenerateServerImpls(::naeem::hottentot::generator::ds::Module *pModule) {
          std::string basePackageName = pModule->package_;
          std::string replacableServerMainTmpStr = serverMainTmpStr_;
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServerMainTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServerMainTmpStr , "[%INDENT%]" , indent_ , 1);
          ::naeem::hottentot::generator::ds::Service *pService;
          std::string registerServicesStr = "";
          for (int i = 0; i < pModule->services_.size(); i++) {
            pService = pModule->services_.at(i);
            std::string serviceName = pService->GetName();
            std::string lowerCaseServiceName = 
              ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(serviceName);
            registerServicesStr += indent_ + indent_ + "Service " + lowerCaseServiceName + "Service = new " +
                                   serviceName + "Impl();\n";
            registerServicesStr += indent_ + indent_ + "serviceRuntime.register(\"127.0.0.1\",2000, " + 
                            lowerCaseServiceName + "Service);\n";              
          }          
          ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServerMainTmpStr ,
                                                                      "[%REGISTER_SERVICES%]" , 
                                                                      registerServicesStr , 1);
          std::string path = serverOutDir_ + "/Main.java";
          ::naeem::hottentot::generator::common::Os::WriteFile(path , 
                                                              replacableServerMainTmpStr);
        }
      } //END NAMESPACE JAVA
    } //END NAMESPACE GENERATOR
  } //END NAMESPACE HOTTENTOT
}  //END NAMESPACE NAEEM#include <sys/stat.h>