#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_H_

#include "tcp_client.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class DefaultTcpClient : public TcpClient {
        public:
          DefaultTcpClient(std::string /* Host */,
                           uint32_t    /* Port */);
          virtual ~DefaultTcpClient();
        public:
          virtual void Connect();
          virtual void Write(unsigned char *         /* data */,
                             uint32_t                /* Length */);
          virtual unsigned char * Read(uint32_t *    /* Pointer to length */);
          virtual void Close();
        };
      }
    }
  }
}

#endif