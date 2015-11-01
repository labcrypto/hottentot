#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_

#include <stdint.h>
#include <string>
#include <map>


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
                    std::map<uint8_t, RequestHandler*> *requestHandlers)
            : host_(host),
              port_(port),
              requestHandlers_(requestHandlers) {
          }
          ~TcpServer() {}
        public:
          virtual void BindAndStart() = 0;
        protected:
          std::string host_;
          uint16_t port_;
          std::map<uint8_t, RequestHandler*> *requestHandlers_;          
        };
      }
    }
  }
}

#endif