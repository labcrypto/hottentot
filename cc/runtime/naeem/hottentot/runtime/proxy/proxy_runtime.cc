#include "proxy_runtime.h"
#include "tcp_client.h"
#include "tcp_client_factory.h"
#include "default_tcp_client_factory.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        TcpClientFactory* ProxyRuntime::tcpClientFactory_ = 0;
        void
        ProxyRuntime::Init(int argc,
                           char **argv) {
        }
        TcpClientFactory*
        ProxyRuntime::GetTcpClientFactory() {
          if (tcpClientFactory_ == 0) {
            tcpClientFactory_ = new DefaultTcpClientFactory;
          }
          return tcpClientFactory_;
        }
      }
    }
  }
}