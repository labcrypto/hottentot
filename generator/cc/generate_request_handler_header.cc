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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <iostream>
#include <fstream>

#include "cc_generator.h"
#include "type_helper.h"

#include "../ds/hot.h"
#include "../ds/service.h"
#include "../ds/method.h"
#include "../ds/module.h"
#include "../ds/argument.h"
#include "../ds/struct.h"
#include "../ds/declaration.h"

#include "../common/os.h"
#include "../common/string_helper.h"
#include "../common/datetime_helper.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace cc {
        void
        CCGenerator::GenerateRequestHandlerHeader(::naeem::hottentot::generator::ds::Service *service,
                                                  ::naeem::hottentot::generator::GenerationConfig &generationConfig,
                                                  std::map<std::string, std::string> &templates) {
          std::string indent = generationConfig.GetIndentString();
          /*
           * Making needed variables and assigning values to them
           */
          std::string serviceNameCamelCaseFirstCapital = 
          ::naeem::hottentot::generator::common::StringHelper::MakeCamelCaseFirstCapital(
            service->GetName()) + "Service";
          std::string serviceNameSnakeCase = 
            ::naeem::hottentot::generator::common::StringHelper::MakeSnakeCaseFromCamelCase(
              serviceNameCamelCaseFirstCapital);
          std::string serviceNameScreamingSnakeCase =
          ::naeem::hottentot::generator::common::StringHelper::MakeScreamingSnakeCaseFromCamelCase(serviceNameSnakeCase);
          std::string serviceInterfaceFilePath = generationConfig.GetOutDir() + "/" + serviceNameSnakeCase + ".h";
          /*
           * Making real values
           */
        }
      }
    }
  }
}