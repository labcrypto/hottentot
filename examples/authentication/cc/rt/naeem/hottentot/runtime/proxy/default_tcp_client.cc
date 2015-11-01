#include "default_tcp_client.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        DefaultTcpClient::DefaultTcpClient(std::string host,
                                           uint32_t port)
            : TcpClient(host, port) {
        }
        DefaultTcpClient::~DefaultTcpClient() {
        }
        void 
        DefaultTcpClient::Connect() {
          // TODO(kamran)
        }
        void 
        DefaultTcpClient::Write(unsigned char *data,
                                uint32_t       dataLength) {
          // TODO(kamran)
        }
        unsigned char * 
        DefaultTcpClient::Read(uint32_t *length) {
          // TODO(kamran)
        }
        void 
        DefaultTcpClient::Close() {
          // TODO(kamran)
        }
      }
    }
  }
}