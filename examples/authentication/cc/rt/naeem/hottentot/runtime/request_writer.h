#ifndef _NAEEM_HOTTENTOT_RUNTIME__REQUEST_WRITER_H_
#define _NAEEM_HOTTENTOT_RUNTIME__REQUEST_WRITER_H_


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class TcpClient;
      class Request;
      class RequestWriter {
      public:
        RequestWriter(TcpClient *tcpClient)
          : tcpClient_(tcpClient) {
        }
        ~RequestWriter() {}
      public:
        virtual void WriteRequest(Request * /* Request object*/);
      private:
        TcpClient *tcpClient_;
      };
    }
  }
}

#endif