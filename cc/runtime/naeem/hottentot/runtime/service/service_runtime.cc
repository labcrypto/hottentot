#include <iostream>

#include "../logger.h"

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
        std::map<Endpoint, std::map<uint8_t, RequestHandler*>*, Endpoint::Comparator> ServiceRuntime::requestHandlers_;
        void
        ServiceRuntime::Init(int argc,
                             char **argv) {
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
            tcpServer->BindAndStart();
            ::naeem::hottentot::runtime::Logger::GetOut() << "Endpoint started: " << it->first.GetHost() << ":" << it->first.GetPort() << std::endl;
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