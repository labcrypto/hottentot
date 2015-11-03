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
      ProtocolV1::ProtocolV1() 
        : currentState_(ZeroState),
          readType_(0),
          readServiceId_(0),
          readMethodId_(0),
          readArgumentCount_(0),
          readingArgumentLength_(0),
          readingCounter(0) {
      }
      ProtocolV1::~ProtocolV1() {
      }
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
      ProtocolV1::ProcessDataForRequest(unsigned char *data,
                                        uint32_t       dataLength) {
        //=========================================================
        for (unsigned int i = 0; i < dataLength; i++) {
          if (currentState_ == ReadingTypeState) {
            readType_ = data[i];
            currentState_ = ReadingServiceIdState;
          } else if (currentState_ == ReadingServiceIdState) {
            readServiceId_ = data[i];
            currentState_ = ReadingMethodIdState;
          } else if (currentState_ == ReadingMethodIdState) {
            readMethodId_ = data[i];
            currentState_ = ReadingArgumentCountState;
          } else if (currentState_ == ReadingArgumentCountState) {
            readArgumentCount_ = data[i];
            readingCounter_ = 0;
            currentState_ = ReadingArgumentLengthState;
          } else if (currentState_ == ReadingArgumentLengthState) {
            if (readingCounter_ == 0) {
              if (data[i] & 0x80 == 0) {
                readingArgumentLength_ = data[i];
                readingCounter_ = 0;
                currentState_ = ReadingArgumentDataState;
              } else {
                targetCounter_ = (data[i] & 0x0f) + 1;
                readingBuffer_.clear();
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
              }
            } else {
              if (readingCounter_ < targetCounter_) {
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
              } else {
                uint32_t temp = 1;
                readingArgumentLength_ = 0;
                for (unsigned int c = targetCounter_ - 1; c > 0; c--) {
                  readingArgumentLength_ += readingBuffer_[c] * temp;
                  temp *= 256;
                }
                readingCounter_ = 0;
                currentState_ = ReadingArgumentDataState;
              }
            }
          }
        } else if (currentState_ == ReadingArgumentDataState) {
          if (readingCounter_ == 0) {
            readingBuffer_.clear();
            readingBuffer_.push_back(data[i]);
            readingCounter_++;
            targetCounter_ = readingArgumentLength_;
          } else {
            
          }
        }

        //=========================================================

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