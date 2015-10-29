#include "request_writer.h"
#include "tcp_client.h"

#include "../protocol_v1.h"
#include "../request.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        void
        RequestWriter::WriteRequest(Request *request) {
          // Serialize request according to HTNP
          ::naeem::hottentot::runtime::Protocol *protocol = 
            new ::naeem::hottentot::runtime::ProtocolV1(); // TODO(kamran): Use factory.
          uint32_t requestSerializedDataLength = 0;
          unsigned char *requestSerilaizedData = protocol->SerializeRequest(request, 
                                                                            &requestSerializedDataLength);
          // Send request byte array
          tcpClient_->Write(requestSerilaizedData, requestSerializedDataLength);
          delete requestSerilaizedData;
          delete protocol; // WARN(kamran): Don't delete if it is a shared pointer and the method is not the owner.
        }
      }
    }
  }
}