#include "service_runtime.h"
#include "service.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        std::vector<_ServiceInfo*> ServiceRuntime::serviceInfos_;
        void
        ServiceRuntime::Register(std::string   host, 
                                 uint32_t      port, 
                                 Service       *service) {
          _ServiceInfo *serviceInfo = new _ServiceInfo;
          serviceInfo->host_ = host;
          serviceInfo->port_ = port;
          serviceInfo->service_ = service;
          serviceInfos_.push_back(serviceInfo);
        }
        void
        ServiceRuntime::Start() {
          for (std::vector<_ServiceInfo*>::iterator it = serviceInfos_.begin();
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