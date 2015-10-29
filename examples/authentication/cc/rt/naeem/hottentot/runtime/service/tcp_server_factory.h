#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_FACTORY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_FACTORY_H_

#include <vector>
#include <string>
#include <stdint.h>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class TcpServer;
        class Service;
        class TcpServerFactory {
        public:
          virtual TcpServer* CreateTcpServer(std::string              /* host */,
                                             uint16_t                 /* port */,
                                             std::vector<Service*> *  /* services */) = 0;
        };
      }
    }
  }
}


#endif
