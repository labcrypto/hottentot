#include "service_runtime.h"
#include "service.h"
#include "service_info.h"
#include "tcp_server.h"
#include "default_client_listener.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        std::vector<ServiceInfo*> ServiceRuntime::serviceInfos_;
        void
        ServiceRuntime::Register(std::string   host, 
                                 uint32_t      port, 
                                 Service       *service) {
          Endpoint endpoint(host, port);
          if (services_.find(endpoint) == std::map::end) {
            std::vector<Service*> *e = new std::vector<Service*>();
            e->push_back(service);
            services_.insert(endpoint, e);
          } else {
            services_.find(endpoint)->second->push_back(service);
          }
        }
        void
        ServiceRuntime::Start() {
          for (std::map<Endpoint, std::vector<Service*>*>::iterator it = services_.begin();
               it != services_.end();
               it++) {
            ::naeem::hottentot::runtime::service::TcpServer *tcpServer = 
              ::naeem::hottentot::runtime::service::TcpServerFactory::CreateTcpServer(it->first->GetHost(), 
                                                                                      it->first->GetPort(),
                                                                                      it->second);
            tcpServer->BindAndStart();
          }
        }
      }
    }
  }
}