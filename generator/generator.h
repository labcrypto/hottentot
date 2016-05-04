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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__GENERATOR_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__GENERATOR_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

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


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
  namespace java {
    class JavaGenerator;
  };
  namespace cc {
    class CCGenerator;
  }
  class Hot;
  class Service;
  class Struct;
  class Method;
  class Module;
  class Argument;
  class Declaration;
  class GenerationConfig {
    friend class ::org::labcrypto::hottentot::generator::cc::CCGenerator;
    friend class ::org::labcrypto::hottentot::generator::java::JavaGenerator;
  public:
    inline std::string GetOutDir() const {
      return outDir_;
    }
    inline void SetOutDir(std::string outDir) {
      outDir_ = outDir;
    }
    inline bool IsSpacesUsedInsteadOfTabsForIndentation() const {
      return spacesUsedInsteadOfTabsForIndentation_;
    }
    inline void SetSpacesUsedInsteadOfTabsForIndentation(bool spacesUsedInsteadOfTabsForIndentation) {
      spacesUsedInsteadOfTabsForIndentation_ = spacesUsedInsteadOfTabsForIndentation;
    }
    inline bool IsMakefileGenerated() const {
      return makefileGenerated_;
    }
    inline void SetMakefileGenerated(bool makefileGenerated) {
      makefileGenerated_ = makefileGenerated;
    }
    inline bool IsClientGenerated() const {
      return clientGenerated_;
    }
    inline void SetClientGenerated(bool clientGenerated) {
      clientGenerated_ = clientGenerated;
    }
    inline bool IsStubGenerated() const {
      return stubGenerated_;
    }
    inline void SetStubGenerated(bool stubGenerated) {
      stubGenerated_ = stubGenerated;
    }
    inline uint8_t GetNumberOfSpacesUsedForIndentation() const {
      return numberOfSpacesUsedForIndentation_;
    }
    inline void SetNumberOfSpacesUsedForIndentation(uint8_t numberOfSpacesUsedForIndentation) {
      numberOfSpacesUsedForIndentation_ = numberOfSpacesUsedForIndentation;
    }
    inline std::string GetIndentString() {
      if (spacesUsedInsteadOfTabsForIndentation_) {
        std::string indent = "";
        for (uint8_t i = 0; i < numberOfSpacesUsedForIndentation_; i++) {
          indent += " ";
        }
        return indent;
      }
      return "\t";
    }
    inline std::string GetExtendModule() {
      return extendModule_;
    }
    inline void SetExtendModule(std::string extendModule) {
      extendModule_ = extendModule;
    }
    inline std::string GetPomGroupId() {
      return pomGroupId_;
    }
    inline void SetPomGroupId(std::string pomGroupId) {
      pomGroupId_ = pomGroupId;
    }
    inline std::string GetPomArtifactId() {
      return pomArtifactId_;
    }
    inline void SetPomArtifactId(std::string pomArtifactId) {
      pomArtifactId_ = pomArtifactId;
    }
    inline std::string GetPomVersion() {
      return pomVersion_;
    }
    inline void SetPomVersion(std::string pomVersion) {
      pomVersion_ = pomVersion;
    }
  private:
    bool makefileGenerated_;
    bool clientGenerated_;
    bool stubGenerated_;
    bool spacesUsedInsteadOfTabsForIndentation_;
    uint8_t numberOfSpacesUsedForIndentation_;
    std::string outDir_;
    std::string extendModule_;
    std::string pomGroupId_;
    std::string pomArtifactId_;
    std::string pomVersion_;
  };
  class Generator {
  public:
    Generator() {}
    virtual ~Generator() {}
  public:
    virtual void Generate (
      ::org::labcrypto::hottentot::generator::Hot *,
      GenerationConfig &
    ) = 0;
  };
}
}
}
}

#endif