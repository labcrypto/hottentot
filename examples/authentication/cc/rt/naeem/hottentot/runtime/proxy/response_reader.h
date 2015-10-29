#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__RESPONSE_READER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__RESPONSE_READER_H_


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Response;
      namespace proxy {
        class TcpClient;
        class ResponseReader {
        public:
          ResponseReader(TcpClient *tcpClient)
            : tcpClient_(tcpClient) {
          }
          ~ResponseReader() {}
        public:
          virtual Response* ReadResponse();
        private:
          TcpClient *tcpClient_;
        };
      }
    }
  }
}

#endif