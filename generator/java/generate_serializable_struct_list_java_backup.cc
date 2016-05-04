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


void 
GenerateSerializableStructListFile (
  std::string listStructName,
  std::string basePackageName,
  std::string replacableSerializableStructListTmpStr,
  std::string outDir,
  std::string indent
) {
  std::string lowerCaseStructName = 
    ::naeem::hottentot::generator::common::StringHelper::MakeLowerCase(listStructName);
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr, 
    "[%BASE_PACKAGE_NAME%]", 
    basePackageName, 
    1
  );
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr, 
    "[%INDENT%]", 
    indent, 
    1
  );
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr, 
    "[%STRUCT_NAME%]", 
    listStructName, 
    1
  );
  ::naeem::hottentot::generator::common::StringHelper::Replace (
    replacableSerializableStructListTmpStr, 
    "[%LOWER_CASE_STRUCT_NAME%]", 
    lowerCaseStructName, 
    1
  );            
  std::string path = outDir + "/Serializable" + listStructName.c_str() + "List.java";
  ::naeem::hottentot::generator::common::Os::WriteFile (
    path, 
    replacableSerializableStructListTmpStr
  );
}

namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  void
  JavaGenerator::GenerateSerializableStructList (
    ::naeem::hottentot::generator::ds::Module *pModule
  ) {
    ::naeem::hottentot::generator::ds::Service *pService;
    std::string basePackageName = pModule->package_;
    for (int i = 0; i < pModule->services_.size(); i++) {
      pService = pModule->services_.at(i);
      std::string serviceName = pService->name_;
      ::naeem::hottentot::generator::ds::Method *pMethod;
      for (int i = 0; i < pService->methods_.size(); i++) {
        pMethod = pService->methods_.at(i);
        std::string lowerCaseReturnType = pMethod->returnType_;
        //TODO do this for args of method and all declaration in struct
        if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pMethod->returnType_)) {
          std::string listStructName = 
            ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pMethod->returnType_);
          GenerateSerializableStructListFile (
            listStructName,
            basePackageName, 
            serializableStructListTmpStr_,
            outDir_, 
            indent_
          );
        }
        ::naeem::hottentot::generator::ds::Argument *pArg;
        for (int i = 0; i < pMethod->arguments_.size(); i++) {
          pArg = pMethod->arguments_.at(i);
          if (::naeem::hottentot::generator::common::TypeHelper::IsListType(pArg->type_)) {
            std::string listStructName =
              ::naeem::hottentot::generator::common::TypeHelper::FetchTypeOfList(pArg->type_);
            GenerateSerializableStructListFile (
              listStructName,
              basePackageName, 
              serializableStructListTmpStr_,
              outDir_, 
              indent_
            );
          }
        }
      }
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org