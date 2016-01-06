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
          /*makefile += "\tmkdir -p lib/runtime\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/logger.cc -o lib/runtime/logger.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/protocol_v1.cc -o lib/runtime/protocol_v1.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/proxy.cc -o lib/runtime/proxy.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/proxy_runtime.cc -o lib/runtime/proxy_runtime.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/default_tcp_client.cc -o lib/runtime/default_tcp_client.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/proxy/default_tcp_client_factory.cc -o lib/runtime/default_tcp_client_factory.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/service/service_runtime.cc -o lib/runtime/service_runtime.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/service/default_tcp_server.cc -o lib/runtime/default_tcp_server.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/service/default_tcp_server_factory.cc -o lib/runtime/default_tcp_server_factory.o\r\n";
          makefile += "\tg++ -c $(RTDIR)/naeem/hottentot/runtime/service/default_request_callback.cc -o lib/runtime/default_request_callback.o\r\n";*/
          for (uint32_t moduleCounter = 0; moduleCounter < hot->modules_.size(); moduleCounter++) {
            std::string objectFiles = "";
            /*objectFiles += "lib/runtime/logger.o lib/runtime/protocol_v1.o lib/runtime/proxy.o lib/runtime/proxy_runtime.o ";
            objectFiles += "lib/runtime/default_tcp_client.o lib/runtime/default_tcp_client_factory.o lib/runtime/service_runtime.o lib/runtime/default_tcp_server.o ";
            objectFiles += "lib/runtime/default_tcp_server_factory.o lib/runtime/default_request_callback.o ";*/
            for (uint32_t structCounter = 0; structCounter < hot->modules_[moduleCounter]->structs_.size(); structCounter++) {
              std::string structName = 
                ::naeem::hottentot::generator::common::StringHelper::MakeSnakeCaseFromCamelCase(
                  hot->modules_[moduleCounter]->structs_[structCounter]->GetName());
              makefile += "\tg++ -c -I/usr/include/hot " + structName + ".cc -o lib/" + structName + ".o\r\n";
              objectFiles += "lib/" + structName + ".o ";
            }
            for (uint32_t serviceCounter = 0; serviceCounter < hot->modules_[moduleCounter]->services_.size(); serviceCounter++) {
              std::string serviceName =
                ::naeem::hottentot::generator::common::StringHelper::MakeSnakeCaseFromCamelCase(
                  hot->modules_[moduleCounter]->services_[serviceCounter]->GetName() + "Service");
              makefile += "\tg++ -c -I/usr/include/hot proxy/" + serviceName + "_proxy.cc -o lib/proxy/" + serviceName + "_proxy.o\r\n";
              makefile += "\tg++ -c -I/usr/include/hot proxy/" + serviceName + "_proxy_builder.cc -o lib/proxy/" + serviceName + "_proxy_builder.o\r\n";
              makefile += "\tg++ -c -I/usr/include/hot service/" + serviceName + "_request_handler.cc -o lib/service/" + serviceName + "_request_handler.o\r\n";
              objectFiles += "lib/proxy/" + serviceName + "_proxy.o ";
              objectFiles += "lib/proxy/" + serviceName + "_proxy_builder.o ";
              objectFiles += "lib/service/" + serviceName + "_request_handler.o ";
              if (generationConfig.IsClientGenerated()) {
                makefile += "\tg++ -c -I/usr/include/hot client/" + serviceName + "_client.cc -o lib/client/" + serviceName + "_client.o\r\n";
                makefile += "\tg++ " + objectFiles + " lib/client/" + serviceName + "_client.o " + " -lhotd -lpthread -o bin/" + serviceName + "_client.out\r\n";
              }
              if (generationConfig.IsStubGenerated()) {
                makefile += "\tg++ -c -I/usr/include/hot stub/" + serviceName + "_impl.cc -o lib/stub/" + serviceName + "_impl.o\r\n";
                makefile += "\tg++ -c -I/usr/include/hot stub/" + serviceName + "_server.cc -o lib/stub/" + serviceName + "_server.o\r\n";
                makefile += "\tg++ " + objectFiles + " lib/stub/" + serviceName + "_impl.o " + "lib/stub/" + serviceName + "_server.o " + " -lhotd -lpthread -o bin/" + serviceName + "_server.out\r\n";
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