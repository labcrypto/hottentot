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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__JAVA__JAVA_GENERATOR_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__JAVA__JAVA_GENERATOR_H_

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>

#include <stdio.h>
#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include "../generator.h"
#include "../module.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  class JavaGenerator : public ::org::labcrypto::hottentot::generator::Generator {
  public:
    JavaGenerator();
    virtual ~JavaGenerator();
  public:
    virtual void Generate (
      ::org::labcrypto::hottentot::generator::Hot *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &
    );
    void GeneratePomFile (
      ::org::labcrypto::hottentot::generator::Hot *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &
    );
    void FakeInsert();
    void GenerateStructs(::org::labcrypto::hottentot::generator::Module*);
    void GenerateEnums(::org::labcrypto::hottentot::generator::Module*);
    void ReadTemplateFiles();
    void GenerateAbstractService(::org::labcrypto::hottentot::generator::Module*);
    void GenerateServiceInterface(::org::labcrypto::hottentot::generator::Module*);
    void GenerateServiceProxyBuilder(::org::labcrypto::hottentot::generator::Module*);
    void GenerateRequestHandler(::org::labcrypto::hottentot::generator::Module*);
    void GenerateServiceProxy(::org::labcrypto::hottentot::generator::Module*);
    void GenerateSerializableStructList(::org::labcrypto::hottentot::generator::Module*);
    void GenerateClientMain(::org::labcrypto::hottentot::generator::Module*);
    void GenerateServerMain(::org::labcrypto::hottentot::generator::Module*);
    void GenerateServerImpls(::org::labcrypto::hottentot::generator::Module*);
    void SetTabStr(::org::labcrypto::hottentot::generator::GenerationConfig &);
    std::string ConvertType(std::string);
    uint32_t GetTypeLength(std::string);
    void Destroy();
  private:
    std::ofstream os;
    std::vector<org::labcrypto::hottentot::generator::Module*>  modules_;
    std::string structTmpStr_;
    std::string enumTmpStr_;
    std::string abstractServiceTmpStr_;
    std::string serviceTmpStr_;
    std::string serviceProxyBuilderTmpStr_;
    std::string requestHandlerTmpStr_;
    std::string serviceProxyTmpStr_;
    std::string serializableStructListTmpStr_;
    std::string clientMainTmpStr_;
    std::string serverMainTmpStr_;
    std::string serverImplTmpStr_;
    std::string outDir_;
    std::string extendModule_;
    std::string clientOutDir_;
    std::string serverOutDir_;
    std::string indent_;
  private:
    static const uint32_t TAB_SPACE_NUMBER = 4;
  };
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org

#endif
