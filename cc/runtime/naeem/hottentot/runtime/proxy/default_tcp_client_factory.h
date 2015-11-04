#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_FACTORY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_FACTORY_H_

#include "tcp_client_factory.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class DefaultTcpClientFactory : public TcpClientFactory {
        public:
          virtual TcpClient* CreateTcpClient(std::string           /* Host */,
                                             uint32_t              /* Port */);
        };
      }
    }
  }
}

#endif