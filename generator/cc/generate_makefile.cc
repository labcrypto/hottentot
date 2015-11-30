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


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace cc {
        void
        CCGenerator::GenerateMakefile(::naeem::hottentot::generator::ds::Hot *hot,
                                      ::naeem::hottentot::generator::GenerationConfig &generationConfig) {
          std::string makefile = "RTDIR = ../../cc/runtime\r\n";
          makefile += "all:\r\n";
          makefile += "\tmkdir -p lib\r\n";
          for (uint32_t moduleCounter = 0; moduleCounter < hot->modules_.size(); moduleCounter++) {
            for (uint32_t structCounter = 0; structCounter < hot->modules_[moduleCounter]->structs_.size(); structCounter++) {
              makefile += "\tg++ -c -I$(RTDIR) " + 
                ::naeem::hottentot::generator::common::StringHelper::MakeSnakeCaseFromCamelCase(
                  hot->modules_[moduleCounter]->structs_[structCounter]->GetName()) + ".cc\r\n";
            }
            for (uint32_t serviceCounter = 0; serviceCounter < hot->modules_[moduleCounter]->services_.size(); serviceCounter++) {
              std::string serviceNam =
                ::naeem::hottentot::generator::common::StringHelper::MakeSnakeCaseFromCamelCase(
                  hot->modules_[moduleCounter]->services_[serviceCounter]->GetName() + "Service");
              makefile += "\tg++ -c -I$(RTDIR) proxy/" + serviceNam + "_proxy.cc\r\n";
              makefile += "\tg++ -c -I$(RTDIR) proxy/" + serviceNam + "_proxy_builder.cc\r\n";
            }
          }
          std::string filename = generationConfig.GetOutDir() + "/Makefile";
          std::fstream f;
          f.open(filename.c_str(), std::fstream::out | std::fstream::binary);
          f << makefile;
          f.close();
        }
      }
    }
  }
}