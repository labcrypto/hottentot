#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_TCP_SERVER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_TCP_SERVER_H_

#include "tcp_server.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class DefaultTcpServer : public TcpServer {
        public:
          DefaultTcpServer(std::string,
                           uint16_t,
                           std::vector<Service*> *);
          virtual ~DefaultTcpServer();
        public:
          virtual void BindAndStart();
        };
      }
    }
  }
}


#endif
