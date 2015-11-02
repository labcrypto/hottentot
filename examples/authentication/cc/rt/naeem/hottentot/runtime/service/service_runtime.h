#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_RUNTIME_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_RUNTIME_H_

#include <stdint.h>
#include <vector>
#include <map>
#include <string>

#include "endpoint.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class Service;
        class RequestHandler;
        class TcpServerFactory;
        class ServiceRuntime {
        public:
          static void Init(int argc, char **argv);
          static void Register(std::string   /* host */, 
                               uint32_t      /* port */, 
                               Service *     /* service implementation */);
          static void Start();
          static TcpServerFactory* GetTcpServerFactory();
          inline static void SetTcpServerFactory(TcpServerFactory *tcpServerFactory) {
            tcpServerFactory_ = tcpServerFactory;
          }
        private:
          static TcpServerFactory *tcpServerFactory_;
          static std::map<Endpoint, std::vector<Service*>*, Endpoint::Comparator> services_;
          static std::map<Endpoint, std::map<uint8_t, RequestHandler*>*, Endpoint::Comparator> requestHandlers_;
          static std::map<Endpoint, std::map<uint8_t, Service*>*, Endpoint::Comparator> impls_;
        };
      }
    }
  }
}

#endif