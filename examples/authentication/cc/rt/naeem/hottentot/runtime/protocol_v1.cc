#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "protocol_v1.h"
#include "request.h"
#include "response.h"
#include "service/request_callback.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      unsigned char* 
      ProtocolV1::SerializeRequest(Request  &request, 
                                   uint32_t *length) {
        uint32_t actualLength = 0;
        actualLength += 1;  // Request type
        actualLength += 1;  // Service Id
        actualLength += 1;  // Method Id
        actualLength += 1;  // Number of arguments
        for (unsigned int i = 0; i < request.GetArgumentCount(); i++) {
          actualLength += request.GetArgumentLength(i) > 127 ? 3 : 1;
          actualLength += request.GetArgumentLength(i);
        }
        *length = actualLength;
        unsigned char *data = new unsigned char[*length];
        unsigned int c = 0;
        data[c++] = request.GetType();
        data[c++] = request.GetServiceId();
        data[c++] = request.GetMethodId();
        data[c++] = request.GetArgumentCount();
        for (unsigned int i = 0; i < request.GetArgumentCount(); i++) {
          if (request.GetArgumentLength(i) > 127) {
            data[c++] = 0x82;
            data[c++] = request.GetArgumentLength(i) / 256;
            data[c++] = request.GetArgumentLength(i) % 256;
          } else {
            data[c++] = request.GetArgumentLength(i);
          }
          unsigned char *argData = request.GetArgumentData(i);
          for (unsigned int j = 0; j < request.GetArgumentLength(i); j++) {
            data[c++] = argData[j];
          }
        }
        if (c != actualLength) {
          std::cerr << "Inconsistency in request serialization process." << std::endl;
          exit(1);
        }
        return data;
      }
      unsigned char* 
      ProtocolV1::SerializeResponse(Response &response, 
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
      bool
      ProtocolV1::IsResponseComplete() {
        return isResponseComplete_;
      }
      Response*
      ProtocolV1::GetResponse() {
        return response_;
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