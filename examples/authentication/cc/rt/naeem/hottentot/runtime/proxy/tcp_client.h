#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__TCP_CLIENT_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__TCP_CLIENT_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class TcpClient {
        public:
          TcpClient(std::string host,
                    uint32_t port)
            : host_(host),
              port_(port) {
          }
          ~TcpClient() {}
        public:
          virtual void Connect() = 0;
          virtual void Write(unsigned char *         /* data */,
                             uint32_t                /* Length */) = 0;
          virtual unsigned char * Read(uint32_t *    /* Pointer to length */) = 0;
          virtual void Close() = 0;
        protected:
          std::string host_;
          uint16_t port_;
        };
      }
    }
  }
}

#endif