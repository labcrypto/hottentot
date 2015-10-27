#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_H_

#include "tcp_server.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class DefaultTcpServer {
        public:
          DefaultTcpServer(ServiceInfo *serviceInfo)
            : serviceInfo_(serviceInfo) {
          }
          ~DefaultTcpServer() {}
        public:
          virtual void BindAndStart() {}
          virtual void SetClientListener(ClientListener *   /* Client listener */) {}
          // virtual unsigned char * Read(uint32_t *           /* Pointer to length */) = 0;
          // virtual void Close() = 0;
        };
      }
    }
  }
}

#endif