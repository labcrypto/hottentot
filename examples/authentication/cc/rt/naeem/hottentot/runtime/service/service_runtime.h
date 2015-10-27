#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_RUNTIME_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_RUNTIME_H_

#include <stdint.h>
#include <vector>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class Service;
        class _ServiceInfo {
        public:
          std::string host_;
          uint32_t port_;
          Service *service_;
        };
        class ServiceRuntime {
        public:
          static void Register(std::string   /* host */, 
                               uint32_t      /* port */, 
                               Service *     /* service implementation */);
          static void Start();
        private:
          static std::vector<_ServiceInfo*> serviceInfos_;
        };
      }
    }
  }
}

#endif