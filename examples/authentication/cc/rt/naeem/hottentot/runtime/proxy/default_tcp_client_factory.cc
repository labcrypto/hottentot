#include "default_tcp_client_factory.h"
#include "default_tcp_client.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        TcpClient* 
        DefaultTcpClientFactory::CreateTcpClient(std::string host,
                                                 uint32_t port) {
          return new DefaultTcpClient(host, port);
        } 
      }
    }
  }
}