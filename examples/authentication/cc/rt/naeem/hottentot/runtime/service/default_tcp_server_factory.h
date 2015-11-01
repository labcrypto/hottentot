#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_TCP_SERVER_FACTORY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_TCP_SERVER_FACTORY_H_

#include "tcp_server_factory.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class DefaultTcpServerFactory : public TcpServerFactory {
        public:
          virtual TcpServer* CreateTcpServer(std::string              /* host */,
                                             uint16_t                 /* port */,
                                             std::vector<Service*> *  /* services */);
        };
      }
    }
  }
}


#endif
