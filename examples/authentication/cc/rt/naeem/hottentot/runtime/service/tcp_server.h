#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__TCP_SERVER_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class ServiceInfo;
        class ClientListener;
        class TcpServer {
        public:
          TcpServer(ServiceInfo *serviceInfo)
            : serviceInfo_(serviceInfo) {
          }
          ~TcpServer() {}
        public:
          virtual void BindAndStart() = 0;
          virtual void SetClientListener(ClientListener *   /* Client listener */) = 0;
          // virtual unsigned char * Read(uint32_t *           /* Pointer to length */) = 0;
          // virtual void Close() = 0;
        protected:
          ServiceInfo *serviceInfo_;
        };
      }
    }
  }
}

#endif