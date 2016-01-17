/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
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
#include "../ds/hot.h"
#include "../common/string_helper.h"
#include "../common/os.h" 
#include "../common/type_helper.h" 
#include "templates/byte_arrays/abstractService.h" 
#include "templates/byte_arrays/requestHandler.h" 
#include "templates/byte_arrays/service.h" 
#include "templates/byte_arrays/serviceProxy.h" 
#include "templates/byte_arrays/serviceProxyBuilder.h" 
#include "templates/byte_arrays/struct.h" 
#include "templates/byte_arrays/serializableStructList.h" 

namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
        JavaGenerator::~JavaGenerator() {
          //
        }
        void
        JavaGenerator::Destroy(){
          //TODO
        }
        JavaGenerator::JavaGenerator() {
          abstractServiceTmpStr_ = abstractServiceTmpStr;
          requestHandlerTmpStr_ = requestHandlerTmpStr;
          serviceTmpStr_ = serviceTmpStr;
          serviceProxyTmpStr_ = serviceProxyTmpStr;
          serviceProxyBuilderTmpStr_ = serviceProxyBuilderTmpStr;
          structTmpStr_ = structTmpStr;
          //MakeStringsFromByteArrays();
          //ReadTemplateFiles();
        }

        void
        JavaGenerator::ReadTemplateFiles() {
          //I dont use this ... 
          ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/struct.template",structTmpStr_);
          ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/abstractService.template",abstractServiceTmpStr_);
          ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/service.template",serviceTmpStr_);
          ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/serviceProxy.template",serviceProxyTmpStr_);
          ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/serviceProxyBuilder.template",serviceProxyBuilderTmpStr_);
          ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/requestHandler.template",requestHandlerTmpStr_);
        }

      
        void
        JavaGenerator::SetTabStr(::naeem::hottentot::generator::GenerationConfig &generationConfig){
          
          if(generationConfig.IsSpacesUsedInsteadOfTabsForIndentation()) {
            for (int i = 0; i < generationConfig.GetNumberOfSpacesUsedForIndentation() ; i++) {
              indent_ += " ";
            }
          }else{
            indent_ = "\t";
          }
        }

        void
        JavaGenerator::Generate(::naeem::hottentot::generator::ds::Hot *hot,
          ::naeem::hottentot::generator::GenerationConfig &generationConfig) {
          SetTabStr(generationConfig);
          //set out dir
          outDir_ = generationConfig.outDir_;
          clientOutDir_ = outDir_ + "/client";
          serverOutDir_ = outDir_ + "/server";
          //
          ::naeem::hottentot::generator::common::Os::MakeDir(outDir_.c_str());
          // std::string serviceFolder = outDir_ + "/service";
          // std::string proxyFolder = outDir_ + "/proxy";
          // ::naeem::hottentot::generator::common::Os::MakeDir(serviceFolder);
          // ::naeem::hottentot::generator::common::Os::MakeDir(proxyFolder);
          modules_ = hot->modules_;
          for (int i = 0; i < modules_.size(); i++) {
            ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);

            GenerateStructs(pModule);
            GenerateAbstractService(pModule);
            GenerateServiceInterface(pModule);
            GenerateRequestHandler(pModule);
            GenerateServiceProxyBuilder(pModule);
            GenerateServiceProxy(pModule);
            //GenerateSerializableStructList(pModule);
          
          }
          Destroy();
        }
        
      } // END NAMESPACE JAVA
    } // END NAMESPACE GENERATOR
  } // END NAMESPACE HOTTENTOT
} // END NAMESPACE NAEEM
