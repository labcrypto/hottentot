#include <iostream>

#include "protocol_v1.h"
#include "request.h"
#include "response.h"
#include "service/request_callback.h"


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
        Request request;
        request.SetType(Request::InvokeStateless);
        request.SetServiceId(1);
        request.SetMethodId(1);
        request.SetArgumentCount(1);
        unsigned char *argData = new unsigned char[5];
        argData[0] = 65;
        argData[1] = 66;
        argData[2] = 67;
        argData[3] = 68;
        argData[4] = 69;
        request.AddArgument(argData, 5);
        Response *response = requestCallback_->OnRequest(this, request);
        if (response) {
          // TODO(kamran) Serialize response
          delete response;
        } else {
          std::cout << "No handler is found." << std::endl;
        }
        delete argData;
      }
      void 
      ProtocolV1::ProcessDataForResponse(unsigned char *dataChunk,
                                         uint32_t       dataChunkLength) {
        // TODO(kamran)
      }
    }
  }
}