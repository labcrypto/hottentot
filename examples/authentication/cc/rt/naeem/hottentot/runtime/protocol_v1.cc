#include "protocol_v1.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      unsigned char* 
      ProtocolV1::SerializeRequest(Request  *request, 
                                   uint32_t *length) {
        // TODO(kamran)
      }
      unsigned char* 
      ProtocolV1::SerializeResponse(Response *response, 
                                    uint32_t *length) {
        // TODO(kamran)
      }
      Response* 
      ProtocolV1::DeserializeRequest(unsigned char  *data, 
                                     uint32_t       dataLength) {
        // TODO(kamran)
      }
      Response* 
      ProtocolV1::DeserializeResponse(unsigned char *data, 
                                      uint32_t       dataLength) {
        // TODO(kamran)
      }
      void 
      ProtocolV1::ProcessDataForRequest(unsigned char *dataChunk,
                                        uint32_t       dataChunkLength) {
        // TODO(kamran)
      }
      void 
      ProtocolV1::ProcessDataForResponse(unsigned char *dataChunk,
                                         uint32_t       dataChunkLength) {
        // TODO(kamran)
      }
    }
  }
}