#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__TCP_CLIENT_FACTORY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__TCP_CLIENT_FACTORY_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class TcpClient;
        class TcpClientFactory {
        public:
          virtual TcpClient* CreateTcpClient(std::string           /* Host */,
                                             uint32_t              /* Port */) = 0;
        };
      }
    }
  }
}

#endif