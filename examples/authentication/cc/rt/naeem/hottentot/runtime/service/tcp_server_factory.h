#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_FACTORY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_FACTORY_H_

#include <map>
#include <string>
#include <stdint.h>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class TcpServer;
        class RequestHandler;
        class TcpServerFactory {
        public:
          virtual TcpServer* CreateTcpServer(std::string                           /* Host */,
                                             uint16_t                              /* Port */,
                                             std::map<uint8_t, RequestHandler*> *  /* Request handlers */) = 0;
        };
      }
    }
  }
}


#endif
