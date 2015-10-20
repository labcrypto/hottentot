#include "htn_runtime.h"
#include "service.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        std::vector<_ServiceInfo*> HtnRuntime::serviceInfos_;
        void
        HtnRuntime::Register(std::string   host, 
                             uint32_t      port, 
                             Service       *service) {
          _ServiceInfo *serviceInfo = new _ServiceInfo;
          serviceInfo->host_ = host;
          serviceInfo->port_ = port;
          serviceInfo->service_ = service;
          serviceInfos_.push_back(serviceInfo);
          // TODO(kamran) Add service object to an array
        }
        void
        HtnRuntime::Start() {
          for (std::vector<_ServiceInfo*>::iterator it = serviceInfos_.begin();
               it != serviceInfos_.end();
               ++it) {
            // TODO(kamran)
          }          
        }
      }
    }
  }
}