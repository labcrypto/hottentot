/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANindent_ILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

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
    ::org::labcrypto::hottentot::generator::Module *pModule
  ) {
    std::string basePackageName = pModule->package_;
    std::string replacableServerMainTmpStr = serverMainTmpStr_;
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacableServerMainTmpStr, 
      "[%BASE_PACKAGE_NAME%]", 
      basePackageName, 
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacableServerMainTmpStr, 
      "[%INDENT%]", 
      indent_, 
      1
    );
    ::org::labcrypto::hottentot::generator::Service *pService;
    std::string registerServicesStr = "";
    for (int i = 0; i < pModule->services_.size(); i++) {
      pService = pModule->services_.at(i);
      std::string serviceName = pService->GetName();
      std::string lowerCaseServiceName = 
        ::org::labcrypto::hottentot::generator::StringHelper::MakeLowerCase(serviceName);
      registerServicesStr += indent_ + indent_ + "Service " + lowerCaseServiceName + "Service = new " +
                             serviceName + "Impl();\n";
      registerServicesStr += indent_ + indent_ + "serviceRuntime.register(\"127.0.0.1\",8080, " + 
                             lowerCaseServiceName + "Service);\n";              
    }          
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacableServerMainTmpStr,
      "[%REGISTER_SERVICES%]", 
      registerServicesStr, 
      1
    );
    std::string packages =
      ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
        ::org::labcrypto::hottentot::generator::StringHelper::Split (
         pModule->GetPackage(), 
          '.'
        ), 
        "/"
      );
    ::org::labcrypto::hottentot::generator::Os::MakeDir(serverOutDir_ + "/" + packages);
    std::string path = serverOutDir_ + "/" + packages + "/SampleServer.java";
    ::org::labcrypto::hottentot::generator::Os::WriteFile (
      path, 
      replacableServerMainTmpStr
    );
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org