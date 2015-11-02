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
        uint32_t 
        DefaultTcpClient::Read(unsigned char *buffer,
                               uint32_t bufferLength) {
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