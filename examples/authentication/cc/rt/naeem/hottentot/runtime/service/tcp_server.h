#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class ServiceInfo;
        class ClientListener;
        class TcpServer {
        public:
          TcpServer(std::string host,
                    uint32_t port,
                    std::vector<Service*> *services)
            : host_(host),
              port_(port),
              services_(service) {
          }
          ~TcpServer() {}
        public:
          virtual void BindAndStart() = 0;
        protected:
          std::string host_;
          uint32_t port_;
          std::vector<Service*> *services_;
        };
      }
    }
  }
}

#endif