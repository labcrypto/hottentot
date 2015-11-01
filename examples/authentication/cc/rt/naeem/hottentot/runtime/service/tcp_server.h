#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_

#include <stdint.h>
#include <string>
#include <vector>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class Service;
        class RequestHandler;
        class TcpServer {
        public:
          TcpServer(std::string host,
                    uint16_t port,
                    std::vector<Service*> *services)
            : host_(host),
              port_(port),
              services_(services) {
          }
          ~TcpServer() {}
        public:
          virtual void BindAndStart() = 0;
        protected:
          std::string host_;
          uint16_t port_;
          std::vector<Service*> *services_;          
        };
      }
    }
  }
}

#endif