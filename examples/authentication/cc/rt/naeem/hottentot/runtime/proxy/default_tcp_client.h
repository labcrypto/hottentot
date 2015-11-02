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
          virtual uint32_t Read(unsigned char *          /* Buffer */,
                                uint32_t                 /* Buffer length */);
          virtual void Close();
        };
      }
    }
  }
}

#endif