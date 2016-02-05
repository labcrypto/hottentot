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
 

#include <stdlib.h>
#include <stdio.h>

#ifndef _MSC_VER
#include <signal.h>
#include <unistd.h>
#endif

#include <iostream>

#include "../logger.h"

#include "service_runtime.h"
#include "service.h"
#include "tcp_server.h"
#include "default_tcp_server_factory.h"

#include "../configuration.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        TcpServerFactory* ServiceRuntime::tcpServerFactory_ = 0;
        std::vector<TcpServer*> ServiceRuntime::tcpServers_;
#ifndef _MSC_VER
        std::vector<pthread_t> ServiceRuntime::threads_;
#else
        std::vector<HANDLE> ServiceRuntime::threads_;
#endif
        std::map<Endpoint, std::vector<Service*>*, Endpoint::Comparator> ServiceRuntime::services_;
        std::map<Endpoint, std::map<uint8_t, RequestHandler*>*, Endpoint::Comparator> ServiceRuntime::requestHandlers_;
#ifndef _MSC_VER
        void 
        ServiceRuntime::SigTermHanlder(int){
          if (::naeem::hottentot::runtime::Configuration::Verbose()) {
            ::naeem::hottentot::runtime::Logger::GetOut() << "SIG_TERM is received ..." << std::endl;
            ::naeem::hottentot::runtime::Logger::GetOut() << "Killing all listener threads ..." << std::endl;
          }
          for (uint32_t i = 0; i < threads_.size(); i++) {
            // TODO: Find a more proper way to kill a thread.
            pthread_kill(threads_[i], SIGKILL);
          }
        }
#else
        BOOL 
        ServiceRuntime::SigTermHanlder(DWORD fdwCtrlType) {
          switch(fdwCtrlType) { 
            case CTRL_C_EVENT: 
            case CTRL_CLOSE_EVENT: 
              if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                ::naeem::hottentot::runtime::Logger::GetOut() << "CONTROL signal is received ..." << std::endl;
                ::naeem::hottentot::runtime::Logger::GetOut() << "Killing all listener threads ..." << std::endl;
              }
              for (uint32_t i = 0; i < threads_.size(); i++) {
                // TODO: Find a more proper way to kill a thread.
                TerminateThread(threads_[i], 0);
              }
              return TRUE;
            default: 
              return FALSE; 
          } 
        }
#endif
        void
        ServiceRuntime::Init(int argc,
                             char **argv) {
          Configuration::Init(argc, argv);
#ifndef _MSC_VER
          struct sigaction sigIntHandler;
          sigIntHandler.sa_handler = ServiceRuntime::SigTermHanlder;
          sigemptyset(&sigIntHandler.sa_mask);
          sigIntHandler.sa_flags = 0;
          sigaction(SIGINT, &sigIntHandler, NULL);
#else
          SetConsoleCtrlHandler((PHANDLER_ROUTINE)SigTermHanlder, TRUE);
#endif
        }
        void
        ServiceRuntime::Shutdown() {
          for (std::map<Endpoint, std::vector<Service*>*, Endpoint::Comparator>::iterator it = services_.begin();
               it != services_.end();
               it++) {
            for (uint32_t i = 0; i < it->second->size(); i++) {
              Service *service = it->second->at(i);
              service->OnShutdown();
              delete service;
            }
            delete it->second;
            delete requestHandlers_[it->first];
          }
          for (uint32_t i = 0; i < tcpServers_.size(); i++) {
            delete tcpServers_[i];
          }
          if (tcpServerFactory_) {
            delete tcpServerFactory_;
          }
        }
        void
        ServiceRuntime::Register(std::string   host, 
                                 uint32_t      port, 
                                 Service       *service) {
          Endpoint endpoint(host, port);
          if (services_.count(endpoint) == 0) {
            std::vector<Service*> *e = new std::vector<Service*>();
            e->push_back(service);
            services_.insert(std::pair<Endpoint, std::vector<Service*>*>(endpoint, e));
          } else {
            services_.find(endpoint)->second->push_back(service);
          }
          service->OnInit();
          if (requestHandlers_.count(endpoint) == 0) {
            std::map<uint8_t, RequestHandler*> *m = new std::map<uint8_t, RequestHandler*>();
            m->insert(std::pair<uint8_t, RequestHandler*>(service->GetServiceId(), service->GetRequestHandler()));
            requestHandlers_.insert(std::pair<Endpoint, std::map<uint8_t, RequestHandler*>*>(endpoint, m));
          } else {
            requestHandlers_.find(endpoint)->second->insert(std::pair<uint8_t, RequestHandler*>(service->GetServiceId(), service->GetRequestHandler()));
          }
        }
        void
        ServiceRuntime::Start() {
          for (std::map<Endpoint, std::vector<Service*>*, Endpoint::Comparator>::iterator it = services_.begin();
               it != services_.end();
               it++) {
            TcpServer *tcpServer = GetTcpServerFactory()->CreateTcpServer(it->first.GetHost(), 
                                                                          it->first.GetPort(), 
                                                                          requestHandlers_.find(it->first)->second);
            tcpServers_.push_back(tcpServer);
            threads_.push_back(tcpServer->BindAndStart());
            if (::naeem::hottentot::runtime::Configuration::Verbose()) {
              ::naeem::hottentot::runtime::Logger::GetOut() << "Endpoint started: " << it->first.GetHost() << ":" << it->first.GetPort() << std::endl;
            }
          }
          for (uint32_t i = 0; i < threads_.size(); i++) {
#ifndef _MSC_VER
            pthread_join(threads_[i], NULL);
#else
            WaitForSingleObject(threads_[i], INFINITE);
#endif
          }
        }
        TcpServerFactory*
        ServiceRuntime::GetTcpServerFactory() {
          if (tcpServerFactory_ == 0) {
            tcpServerFactory_ = new DefaultTcpServerFactory;
          }
          return tcpServerFactory_;
        }
      }
    }
  }
}