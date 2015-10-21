#ifndef _NAEEM_HOTTENTOT_RUNTIME__TCP_CLIENT_H_
#define _NAEEM_HOTTENTOT_RUNTIME__TCP_CLIENT_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class TcpClient {
      public:
        TcpClient() {}
        ~TcpClient() {}
      public:
        virtual void Connect(std::string           /* Host */,
                             uint32_t              /* Port */) = 0;
        virtual void Write(unsigned char *         /* data */,
                           uint32_t                /* Length */) = 0;
        virtual unsigned char * Read(uint32_t *    /* Pointer to length */) = 0;
        virtual void Close() = 0;
      };
    }
  }
}

#endif