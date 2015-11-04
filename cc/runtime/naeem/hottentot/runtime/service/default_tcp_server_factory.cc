#include "default_tcp_server_factory.h"
#include "default_tcp_server.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        TcpServer*
        DefaultTcpServerFactory::CreateTcpServer(std::string host,
                                                 uint16_t port,
                                                 std::map<uint8_t, RequestHandler*> *requestHandlers) {
          return new DefaultTcpServer(host, port, requestHandlers);
        }
      }
    }
  }
}