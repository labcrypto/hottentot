#ifndef _NAEEM_HOTTENTOT_RUNTIME__DEFAULT_TCP_CLIENT_H_
#define _NAEEM_HOTTENTOT_RUNTIME__DEFAULT_TCP_CLIENT_H_

#include <stdint.h>
#include <string>

#include "tcp_client.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class DefaultTcpClient : public TcpClient {
      public:
        DefaultTcpClient() {}
        ~DefaultTcpClient() {}
      public:
        virtual void Connect(std::string           /* Host */,
                             uint32_t              /* Port */) {}
        virtual void Write(unsigned char *         /* data */,
                           uint32_t                /* Length */) {}
        virtual unsigned char * Read(uint32_t *    /* Pointer to length */) {}
        virtual void Close() {}
      };
    }
  }
}

#endif