#include "response_reader.h"
#include "protocol_v1.h"
#include "response.h"
#include "tcp_client.h"

namespace naeem {
  namespace hottentot {
    namespace runtime {
      Response*
      ResponseReader::ReadResponse() {
        // Read response byte array
        uint32_t responseSerializedDataLength = 0;
        // TODO(kamran): Read operation should be buffered.
        unsigned char *responseSerializedData = tcpClient_->Read(&responseSerializedDataLength);
        // Deserialize request according to HTNP
        ::naeem::hottentot::runtime::Protocol *protocol = 
          new ::naeem::hottentot::runtime::ProtocolV1(); // TODO(kamran): Use factory.        
        ::naeem::hottentot::runtime::Response *response = protocol->DeserializeResponse(responseSerializedData, 
                                                                                        responseSerializedDataLength);
        delete responseSerializedData;
        delete protocol; // WARN(kamran): Don't delete if it is a shared pointer and the method is not the owner.
      }
    }
  }
}