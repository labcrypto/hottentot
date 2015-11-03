#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_TCP_SERVER_FACTORY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_TCP_SERVER_FACTORY_H_

#include "tcp_server_factory.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class DefaultTcpServerFactory : public TcpServerFactory {
        public:
          virtual TcpServer* CreateTcpServer(std::string                           /* Host */,
                                             uint16_t                              /* Port */,
                                             std::map<uint8_t, RequestHandler*> *  /* Request handlers */);
        };
      }
    }
  }
}


#endif
