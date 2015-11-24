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

#ifndef _NAEEM_HOTTENTOT_GENERATOR__GENERATOR_H_
#define _NAEEM_HOTTENTOT_GENERATOR__GENERATOR_H_

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java{
        class JavaGenerator;
      };
      namespace ds {
        class Hot;
        class Service;
        class Method;
        class Module;
        class Argument;
        class Declaration;
      }
      class GenerationConfig {

      friend class ::naeem::hottentot::generator::java::JavaGenerator;
      public:
        inline std::string GetOutDir() const {
          return outDir_;
        }
        inline void SetOutDir(std::string outDir) {
          outDir_ = outDir;
        }
      private:
        std::string outDir_;
      };
      class Generator {
      public:
        Generator() {}
        virtual ~Generator() {}
      public:
        virtual void Generate(::naeem::hottentot::generator::ds::Hot *,
                              GenerationConfig &) = 0;
      };
    }
  }
}

#endif