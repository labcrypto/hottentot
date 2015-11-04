#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__PROXY_RUNTIME_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__PROXY_RUNTIME_H_

#include <stdint.h>
#include <vector>
#include <map>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class TcpClientFactory;
        class ProxyRuntime {
        public:
          static void Init(int argc, char **argv);
          static TcpClientFactory* GetTcpClientFactory();
          inline static void SetTcpClientFactory(TcpClientFactory *tcpClientFactory) {
            tcpClientFactory_ = tcpClientFactory;
          }
        private:
          static TcpClientFactory *tcpClientFactory_;
        };
      }
    }
  }
}

#endif