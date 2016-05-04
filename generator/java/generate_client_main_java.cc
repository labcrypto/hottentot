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
  JavaGenerator::GenerateClientMain (
    ::org::labcrypto::hottentot::generator::Module *pModule
  ) {
    std::string basePackageName = pModule->package_;
    std::string replacableClientMainTmpStr = clientMainTmpStr_;
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacableClientMainTmpStr, 
      "[%BASE_PACKAGE_NAME%]", 
      basePackageName, 
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacableClientMainTmpStr, 
      "[%INDENT%]", 
      indent_, 
      1
    );
    std::string importProxiesStr = "";
    std::string allProxiesStr = "";
    ::org::labcrypto::hottentot::generator::Service *pService;
    for (int i = 0; i < pModule->services_.size(); i++) {
      pService = pModule->services_.at(i);
      std::string serviceName = pService->GetName();
      std::string lowerCaseServiceName = 
      ::org::labcrypto::hottentot::generator::StringHelper::MakeLowerCase(serviceName);
      importProxiesStr += "import " + basePackageName + "." +
                          serviceName +  "Service;\n";
      importProxiesStr += "import " + basePackageName + "." +
                          serviceName  + "ServiceProxyBuilder;\n";
      allProxiesStr += indent_ + indent_ + "final " + serviceName + "Service " +
                        lowerCaseServiceName + "Proxy = " + serviceName +
                        "ServiceProxyBuilder.create(\"127.0.0.1\", 8080);\n";
    }
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacableClientMainTmpStr,
      "[%ALL_PROXIES%]", 
      allProxiesStr,
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacableClientMainTmpStr,
      "[%IMPORT_PROXIES%]", 
      importProxiesStr, 
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
    ::org::labcrypto::hottentot::generator::Os::MakeDir(clientOutDir_ + "/" + packages);
    std::string path = clientOutDir_ + "/" + packages + "/SampleClient.java";
    ::org::labcrypto::hottentot::generator::Os::WriteFile (
      path, 
      replacableClientMainTmpStr
    );
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org