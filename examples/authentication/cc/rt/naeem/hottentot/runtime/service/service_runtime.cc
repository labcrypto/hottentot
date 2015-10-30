#include <iostream>

#include "service_runtime.h"
#include "service.h"
#include "tcp_server.h"
#include "default_tcp_server_factory.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        TcpServerFactory* ServiceRuntime::tcpServerFactory_ = 0;
        std::map<Endpoint, std::vector<Service*>*, Endpoint::Comparator> ServiceRuntime::services_;
        void
        ServiceRuntime::Init(int argc,
                             char **argv) {
        }
        void
        ServiceRuntime::Register(std::string   host, 
                                 uint32_t      port, 
                                 Service       *service) {
          Endpoint endpoint(host, port);
          std::cout << "Size: " << services_.size() << std::endl;
          std::cout << "Adding entry " << host << ":" << port << std::endl;
          if (services_.count(endpoint) == 0) {
            std::cout << "Making a new entry ..." << std::endl;
            std::vector<Service*> *e = new std::vector<Service*>();
            e->push_back(service);
            services_.insert(std::pair<Endpoint, std::vector<Service*>*>(endpoint, e));
          } else {
            std::cout << "Adding to available entry ..." << std::endl;
            services_.find(endpoint)->second->push_back(service);
          }
        }
        void
        ServiceRuntime::Start() {
          for (std::map<Endpoint, std::vector<Service*>*, Endpoint::Comparator>::iterator it = services_.begin();
               it != services_.end();
               it++) {
            std::cout << "Starting endpoint: " << it->first.GetHost() << ":" << it->first.GetPort() << " >> " << it->second->size() << std::endl;
            TcpServer *tcpServer = GetTcpServerFactory()->CreateTcpServer(it->first.GetHost(), 
                                                                          it->first.GetPort(), 
                                                                          it->second);
            tcpServer->BindAndStart();
          }
          while(true);
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