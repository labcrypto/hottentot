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

#include <iostream>
#include <fstream>

#include "cc_generator.h"
#include "type_helper.h"

#include "../hot.h"
#include "../service.h"
#include "../method.h"
#include "../module.h"
#include "../argument.h"
#include "../struct.h"
#include "../declaration.h"
#include "../os.h"
#include "../string_helper.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace cc {
  void
  CCGenerator::GenerateMakefile (
    ::org::labcrypto::hottentot::generator::Hot *hot,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig
  ) {
    std::string makefile = "";
    // makefile += "RTDIR = ../../../cc/runtime\r\n";
    makefile += "all:\r\n";
    makefile += "\tmkdir -p bin\r\n";
    makefile += "\tmkdir -p lib\r\n";
    makefile += "\tmkdir -p lib/proxy\r\n";
    makefile += "\tmkdir -p lib/service\r\n";
    if (generationConfig.IsClientGenerated()) {
      makefile += "\tmkdir -p lib/client\r\n";
    }
    if (generationConfig.IsStubGenerated()) {
      makefile += "\tmkdir -p lib/stub\r\n";
    }
    for (uint32_t moduleCounter = 0; moduleCounter < hot->modules_.size(); moduleCounter++) {
      std::string objectFiles = "";
      for (uint32_t structCounter = 0; structCounter < hot->modules_[moduleCounter]->structs_.size(); structCounter++) {
        std::string structName = 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeSnakeCaseFromCamelCase (
            hot->modules_[moduleCounter]->structs_[structCounter]->GetName()
          );
        makefile += "\tg++ -Wall -g -c -I/usr/local/include/hot " + structName + 
          ".cc -o lib/" + structName + ".o\r\n";
        objectFiles += "lib/" + structName + ".o ";
      }
      for (uint32_t serviceCounter = 0; serviceCounter < hot->modules_[moduleCounter]->services_.size(); serviceCounter++) {
        std::string serviceName =
          ::org::labcrypto::hottentot::generator::StringHelper::MakeSnakeCaseFromCamelCase (
            hot->modules_[moduleCounter]->services_[serviceCounter]->GetName() + "Service"
          );
        makefile += "\tg++ -Wall -g -c -I/usr/local/include/hot proxy/" + 
          serviceName + "_proxy.cc -o lib/proxy/" + serviceName + "_proxy.o\r\n";
        makefile += "\tg++ -Wall -g -c -I/usr/local/include/hot proxy/" + 
          serviceName + "_proxy_builder.cc -o lib/proxy/" + serviceName + "_proxy_builder.o\r\n";
        makefile += "\tg++ -Wall -g -c -I/usr/local/include/hot service/" + 
          serviceName + "_request_handler.cc -o lib/service/" + serviceName + "_request_handler.o\r\n";
        objectFiles += "lib/proxy/" + serviceName + "_proxy.o ";
        objectFiles += "lib/proxy/" + serviceName + "_proxy_builder.o ";
        objectFiles += "lib/service/" + serviceName + "_request_handler.o ";
        if (generationConfig.IsClientGenerated()) {
          makefile += "\tg++ -Wall -g -c -I/usr/local/include/hot client/" + 
            serviceName + "_client.cc -o lib/client/" + serviceName + "_client.o\r\n";
          makefile += "\tg++ " + objectFiles + " lib/client/" + 
            serviceName + "_client.o " + " -lhotd -lpthread -o bin/" + serviceName + "_client.out\r\n";
        }
        if (generationConfig.IsStubGenerated()) {
          makefile += "\tg++ -Wall -g -c -I/usr/local/include/hot stub/" + 
            serviceName + "_impl.cc -o lib/stub/" + serviceName + "_impl.o\r\n";
          makefile += "\tg++ -Wall -g -c -I/usr/local/include/hot stub/" + 
            serviceName + "_server.cc -o lib/stub/" + serviceName + "_server.o\r\n";
          makefile += "\tg++ " + objectFiles + " lib/stub/" + 
            serviceName + "_impl.o " + "lib/stub/" + serviceName + "_server.o " + " -lhotd -lpthread -o bin/" + serviceName + "_server.out\r\n";
        }
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
}