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

#include "templates/byte_arrays/abstractService.h" 
#include "templates/byte_arrays/requestHandler.h" 
#include "templates/byte_arrays/service.h" 
#include "templates/byte_arrays/serviceProxy.h" 
#include "templates/byte_arrays/serviceProxyBuilder.h" 
#include "templates/byte_arrays/struct.h" 
#include "templates/byte_arrays/serializableStructList.h" 
#include "templates/byte_arrays/clientMain.h" 
#include "templates/byte_arrays/serverMain.h" 
#include "templates/byte_arrays/serverImpl.h" 
#include "templates/byte_arrays/enum.h" 
#include "templates/byte_arrays/pom.h" 

#include "../hot.h"
#include "../string_helper.h"
#include "../os.h" 
#include "../type_helper.h" 


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  JavaGenerator::~JavaGenerator() {
  }
  void
  JavaGenerator::Destroy(){
  }
  JavaGenerator::JavaGenerator() {
    abstractServiceTmpStr_ = abstractServiceTmpStr;
    requestHandlerTmpStr_ = requestHandlerTmpStr;
    serviceTmpStr_ = serviceTmpStr;
    serviceProxyTmpStr_ = serviceProxyTmpStr;
    serviceProxyBuilderTmpStr_ = serviceProxyBuilderTmpStr;
    structTmpStr_ = structTmpStr;
    serializableStructListTmpStr_ = serializableStructListTmpStr;
    clientMainTmpStr_ = clientMainTmpStr;
    serverMainTmpStr_ = serverMainTmpStr;
    serverImplTmpStr_ = serverImplTmpStr;
    enumTmpStr_ = enumTmpStr;
    pomTmpStr_ = pomTmpStr;
  }
  void
  JavaGenerator::ReadTemplateFiles() {
  }
  void
  JavaGenerator::SetTabStr(::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig) {
    if (generationConfig.IsSpacesUsedInsteadOfTabsForIndentation()) {
      for (int i = 0; i < generationConfig.GetNumberOfSpacesUsedForIndentation(); i++) {
        indent_ += " ";
      }
    } else {
      indent_ = "\t";
    }
  }
  void
  JavaGenerator::Generate (
    ::org::labcrypto::hottentot::generator::Hot *hot,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig
  ) {
    SetTabStr(generationConfig);
    extendModule_ = generationConfig.extendModule_;
    outDir_ = generationConfig.outDir_ + "/src/main/hot";
    clientOutDir_ = generationConfig.outDir_ + "/src/main/hot-client-sample";
    serverOutDir_ = generationConfig.outDir_ + "/src/main/hot-server-sample";
    ::org::labcrypto::hottentot::generator::Os::MakeDir(outDir_.c_str());
    ::org::labcrypto::hottentot::generator::Os::MakeDir(clientOutDir_.c_str());
    ::org::labcrypto::hottentot::generator::Os::MakeDir(serverOutDir_.c_str());
    modules_ = hot->modules_;
    for (int i = 0; i < modules_.size(); i++) {
      ::org::labcrypto::hottentot::generator::Module *pModule = modules_.at(i);
      GenerateEnums(pModule);
      GenerateStructs(pModule);
      GenerateAbstractService(pModule);
      GenerateServiceInterface(pModule);
      GenerateRequestHandler(pModule);
      GenerateServiceProxyBuilder(pModule);
      GenerateServiceProxy(pModule);
      GenerateSerializableStructList(pModule);
      GenerateClientMain(pModule);
      GenerateServerMain(pModule);
      GenerateServerImpls(pModule);
    }
    Destroy();
  }
  void
  JavaGenerator::GeneratePomFile (
    ::org::labcrypto::hottentot::generator::Hot *hot,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig
  ) {
    std::string replacablePomTmpStr = pomTmpStr_;
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacablePomTmpStr, 
      "[%POM_GROUP_ID%]", 
      generationConfig.GetPomGroupId(), 
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacablePomTmpStr, 
      "[%POM_ARTIFACT_ID%]", 
      generationConfig.GetPomArtifactId(), 
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacablePomTmpStr, 
      "[%POM_VERSION%]", 
      generationConfig.GetPomVersion(), 
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacablePomTmpStr, 
      "[%HOT_DIR_PATH%]", 
      outDir_, 
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacablePomTmpStr, 
      "[%HOT_SAMPLE_CLIENT_DIR_PATH%]", 
      clientOutDir_, 
      1
    );
    ::org::labcrypto::hottentot::generator::StringHelper::Replace (
      replacablePomTmpStr, 
      "[%HOT_SAMPLE_SERVER_DIR_PATH%]", 
      serverOutDir_, 
      1
    );
    ::org::labcrypto::hottentot::generator::Os::WriteFile (
      generationConfig.GetOutDir() + "/pom.xml", 
      replacablePomTmpStr
    );
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NMAESPACE org
