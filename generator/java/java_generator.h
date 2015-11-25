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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__JAVA__JAVA_GENERATOR_H_
#define _NAEEM_HOTTENTOT_GENERATOR__JAVA__JAVA_GENERATOR_H_

#include "../generator.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <fstream>
#include <map>
#include "../ds/module.h"

namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
        class JavaGenerator : public ::naeem::hottentot::generator::Generator {
        public:
          JavaGenerator();
          virtual ~JavaGenerator();
        public:
          virtual void Generate(::naeem::hottentot::generator::ds::Hot *,
                                ::naeem::hottentot::generator::GenerationConfig &);

          void FakeInsert();
          void GenerateStructs(::naeem::hottentot::generator::ds::Module*);
          void ReadTemplateFiles();
          void GenerateAbstractService(::naeem::hottentot::generator::ds::Module*);
          void GenerateServiceInterface(::naeem::hottentot::generator::ds::Module*);
          void GenerateServiceProxyBuilder(::naeem::hottentot::generator::ds::Module*);
          void GenerateRequestHandler(::naeem::hottentot::generator::ds::Module*);
          void GenerateServiceProxy(::naeem::hottentot::generator::ds::Module*);
          void MakeTabStr(::naeem::hottentot::generator::GenerationConfig &);
          std::string ConvertType(std::string);
          uint32_t GetTypeLength(std::string);
          
        private:
          std::ofstream os;
          std::vector<naeem::hottentot::generator::ds::Module*>  modules_;
          std::string structTmpStr_;
          std::string abstractServiceTmpStr_;
          std::string serviceTmpStr_;
          std::string serviceProxyBuilderTmpStr_;
          std::string requestHandlerTmpStr_;
          std::string serviceProxyTmpStr_;
          std::string outDir_;
          static const uint32_t TAB_SPACE_NUMBER = 4;
          std::string TAB_STR_;
        };
      }
    }
  }
}

#endif
