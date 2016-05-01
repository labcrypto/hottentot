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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__CC__CC_GENERATOR_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__CC__CC_GENERATOR_H_

#include <map>
#include <string>
 
#include "../generator.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace cc {
  class CCGenerator : public ::org::labcrypto::hottentot::generator::Generator {
  public:
    CCGenerator() {}
    virtual ~CCGenerator() {}
  public:
    virtual void 
    Generate (
      ::org::labcrypto::hottentot::generator::ds::Hot *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &
    );
    virtual void 
    GenerateMakefile (
      ::org::labcrypto::hottentot::generator::ds::Hot *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &
    );
    virtual void 
    GenerateClient (
      ::org::labcrypto::hottentot::generator::ds::Hot *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &
    );
    virtual void 
    GenerateStub (
      ::org::labcrypto::hottentot::generator::ds::Hot *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &
    );
  protected:
    virtual void 
    GenerateEnums (
      std::vector< ::org::labcrypto::hottentot::generator::ds::Module*>,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateInterface (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateServiceInterface (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyHeader (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyCC (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual std::string 
    GenerateProxyCCMethod (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::ds::Method *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual std::string 
    GenerateProxyCCMethodArgumentSerialization (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::ds::Method *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyBuilderHeader (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyBuilderCC (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateStructHeader (
      ::org::labcrypto::hottentot::generator::ds::Struct *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateStructCC (
      ::org::labcrypto::hottentot::generator::ds::Struct *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateAbstractServiceHeader (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateRequestHandlerHeader (
      ::org::labcrypto::hottentot::generator::ds::Service *,
      ::org::labcrypto::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateRequestHandlerCC (
      ::org::labcrypto::hottentot::generator::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual std::string 
    GenerateRequestHandlerCCMethodIfClause (
      ::org::labcrypto::hottentot::generator::Service *,
      ::org::labcrypto::hottentot::generator::Method *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );    
  };
}
}
}
}
}

#endif
