#include "default_tcp_server.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        DefaultTcpServer::DefaultTcpServer(std::string host,
                                           uint16_t port,
                                           std::vector<Service*> *services)
            : TcpServer(host, port, services) {
        }
        DefaultTcpServer::~DefaultTcpServer() {
        }
        void
        DefaultTcpServer::BindAndStart() {
          // TODO(kamran)
        }
      }
    }
  }
}