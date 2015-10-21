#ifndef _NAEEM_HOTTENTOT_RUNTIME__RESPONSE_READER_H_
#define _NAEEM_HOTTENTOT_RUNTIME__RESPONSE_READER_H_


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Response;
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

#endif