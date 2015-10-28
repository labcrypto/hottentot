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
        class ServiceInfo;
        class ServiceRuntime {
        public:
          static void Register(std::string   /* host */, 
                               uint32_t      /* port */, 
                               Service *     /* service implementation */);
          static void Start();
        private:
          static std::map<Endpoint, std::vector<Service*>*> services_;
        };
      }
    }
  }
}

#endif