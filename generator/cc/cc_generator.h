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
  class CCGenerator : public ::naeem::hottentot::generator::Generator {
  public:
    CCGenerator() {}
    virtual ~CCGenerator() {}
  public:
    virtual void 
    Generate (
      ::naeem::hottentot::generator::ds::Hot *,
      ::naeem::hottentot::generator::GenerationConfig &
    );
    virtual void 
    GenerateMakefile (
      ::naeem::hottentot::generator::ds::Hot *,
      ::naeem::hottentot::generator::GenerationConfig &
    );
    virtual void 
    GenerateClient (
      ::naeem::hottentot::generator::ds::Hot *,
      ::naeem::hottentot::generator::GenerationConfig &
    );
    virtual void 
    GenerateStub (
      ::naeem::hottentot::generator::ds::Hot *,
      ::naeem::hottentot::generator::GenerationConfig &
    );
  protected:
    virtual void 
    GenerateEnums (
      std::vector< ::naeem::hottentot::generator::ds::Module*>,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateInterface (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateServiceInterface (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyHeader (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyCC (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual std::string 
    GenerateProxyCCMethod (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::ds::Method *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual std::string 
    GenerateProxyCCMethodArgumentSerialization (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::ds::Method *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyBuilderHeader (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateProxyBuilderCC (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateStructHeader (
      ::naeem::hottentot::generator::ds::Struct *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateStructCC (
      ::naeem::hottentot::generator::ds::Struct *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateAbstractServiceHeader (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateRequestHandlerHeader (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual void 
    GenerateRequestHandlerCC (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::GenerationConfig &,
      std::map<std::string, std::string> &
    );
    virtual std::string 
    GenerateRequestHandlerCCMethodIfClause (
      ::naeem::hottentot::generator::ds::Service *,
      ::naeem::hottentot::generator::ds::Method *,
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
