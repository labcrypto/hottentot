#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "protocol_v1.h"
#include "request.h"
#include "response.h"
#include "service/request_callback.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      ProtocolV1::ProtocolV1(int remoteSocketFD) 
        : Protocol(remoteSocketFD),
          currentState_(ReadingLengthState),
          readingLength_(0),
          readingCounter_(0),
          targetCounter_(0),
          isResponseComplete_(false) {
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
      Request* 
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
        for (unsigned int i = 0; i < dataLength; i++) {
          if (currentState_ == ReadingLengthState) {
            if (readingCounter_ == 0) {
              if (data[i] & 0x80 == 0) {
                readingLength_ = data[i];
                readingCounter_ = 0;
                currentState_ = ReadingDataState;
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
                readingLength_ = 0;
                for (unsigned int c = targetCounter_ - 1; c > 0; c--) {
                  readingLength_ += readingBuffer_[c] * temp;
                  temp *= 256;
                }
                readingCounter_ = 0;
                currentState_ = ReadingDataState;
              }
            }
          } else if (currentState_ == ReadingDataState) {
            if (readingCounter_ == 0) {
              readingBuffer_.clear();
              readingBuffer_.push_back(data[i]);
              readingCounter_++;
              targetCounter_ = readingLength_;
            } else {
              if (readingCounter_ < targetCounter_) {
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
              } else {
                uint32_t requestLength = readingLength_;
                unsigned char *requestData = new unsigned char[requestLength];
                for (unsigned int c = 0; c < requestLength; c++) {
                  requestData[c] = readingBuffer_[c];
                }
                Request *request = DeserializeRequest(requestData, requestLength);
                readingBuffer_.clear();
                readingCounter_ = 0;
                currentState_ = ReadingLengthState;
                Response *response = requestCallback_->OnRequest(this, *request);
                if (response) {
                  uint32_t responseSerializedLength = 0;
                  unsigned char *responseSerializedData = SerializeResponse(*response, &responseSerializedLength);
                  write(remoteSocketFD_, responseSerializedData, responseSerializedLength * sizeof(unsigned char));
                  delete responseSerializedData;
                  delete response;
                } else {
                  std::cout << "No handler is found." << std::endl;
                }
                delete requestData;
              }
            }
          }
        }
      }
      void 
      ProtocolV1::ProcessDataForResponse(unsigned char *data,
                                         uint32_t       dataLength) {
        for (unsigned int i = 0; i < dataLength; i++) {
          if (currentState_ == ReadingLengthState) {
            if (readingCounter_ == 0) {
              if (data[i] & 0x80 == 0) {
                isResponseComplete_ = false;
                readingLength_ = data[i];
                readingCounter_ = 0;
                currentState_ = ReadingDataState;
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
                readingLength_ = 0;
                for (unsigned int c = targetCounter_ - 1; c > 0; c--) {
                  readingLength_ += readingBuffer_[c] * temp;
                  temp *= 256;
                }
                readingCounter_ = 0;
                currentState_ = ReadingDataState;
              }
            }
          } else if (currentState_ == ReadingDataState) {
            if (readingCounter_ == 0) {
              readingBuffer_.clear();
              readingBuffer_.push_back(data[i]);
              readingCounter_++;
              targetCounter_ = readingLength_;
            } else {
              if (readingCounter_ < targetCounter_) {
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
              } else {
                uint32_t responseLength = readingLength_;
                unsigned char *responseData = new unsigned char[responseLength];
                for (unsigned int c = 0; c < responseLength; c++) {
                  responseData[c] = readingBuffer_[c];
                }
                response_ = DeserializeResponse(responseData, responseLength);
                readingBuffer_.clear();
                readingCounter_ = 0;
                currentState_ = ReadingLengthState;
                isResponseComplete_ = true;
                delete responseData;
              }
            }
          }
        }
      }
    }
  }
}