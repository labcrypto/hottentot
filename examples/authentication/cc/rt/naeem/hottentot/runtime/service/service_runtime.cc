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
          ServiceInfo *serviceInfo = new ServiceInfo;
          serviceInfo->SetHost(host);
          serviceInfo->SetPort(port);
          serviceInfo->SetService(service);
          serviceInfos_.push_back(serviceInfo);
        }
        void
        ServiceRuntime::Start() {
          for (std::vector<ServiceInfo*>::iterator it = serviceInfos_.begin();
               it != serviceInfos_.end();
               ++it) {
            ::naeem::hottentot::runtime::service::TcpServer *tcpServer = 
              ::naeem::hottentot::runtime::service::TcpServerFactory::CreateTcpServer(*it);
            tcpServer->BindAndStart();
            tcpServer->SetClientListener(new ::naeem::hottentot::runtime::service::DefaultClientListener(*it));
          }
        }
      }
    }
  }
}