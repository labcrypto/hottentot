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
                           std::map<uint8_t, RequestHandler*> *);
          virtual ~DefaultTcpServer();
        public:
          virtual void BindAndStart();
        private:
          static void* AcceptClients(void *);
          static void* HandleClientConnection(void *);
        private:
          int serverSocketFD_;
        };
        class _HandleClientConnectionParams {
        public:
          DefaultTcpServer *tcpServer_;
          int clientSocketFD_;
        };
      }
    }
  }
}


#endif
