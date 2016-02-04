/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _MSC_VER
// #include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#endif

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#include <unistd.h>
#endif

#include "protocol_v1.h"
#include "request.h"
#include "logger.h"
#include "utils.h"
#include "response.h"
#include "configuration.h"
#include "service/request_callback.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      ProtocolV1::ProtocolV1(int remoteSocketFD) 
        : Protocol(remoteSocketFD),
          isResponseComplete_(false),
          readingLength_(0),
          readingCounter_(0),
          targetCounter_(0),
          currentState_(ReadingLengthState) {
      }
      ProtocolV1::~ProtocolV1() {
      }
      bool
      ProtocolV1::IsResponseComplete() {
        return isResponseComplete_;
      }
      Response*
      ProtocolV1::GetResponse() {
        return response_;
      }
      unsigned char* 
      ProtocolV1::SerializeRequest(Request  &request, 
                                   uint32_t *length) {
        uint32_t actualLength = 0;
        actualLength += 1;  // Request type
        actualLength += 4;  // Service Id
        actualLength += 4;  // Method Id
        actualLength += 1;  // Number of arguments
        for (unsigned int i = 0; i < request.GetArgumentCount(); i++) {
          if (request.GetArgumentLength(i) < 128) {
            actualLength += 1;
            actualLength += request.GetArgumentLength(i);
          } else if (request.GetArgumentLength(i) < 256) {
            actualLength += 2;
            actualLength += request.GetArgumentLength(i);
          } else if (request.GetArgumentLength(i) < 256 * 256) {
            actualLength += 3;
            actualLength += request.GetArgumentLength(i);
          } else if (request.GetArgumentLength(i) < 256 * 256 * 256) {
            actualLength += 4;
            actualLength += request.GetArgumentLength(i);
          }
        }
        *length = actualLength;
        unsigned char *data = new unsigned char[*length];
        unsigned int c = 0;
        data[c++] = request.GetType();
        uint32_t serviceId = request.GetServiceId();
        data[c++] = ((unsigned char *)&serviceId)[3];
        data[c++] = ((unsigned char *)&serviceId)[2];
        data[c++] = ((unsigned char *)&serviceId)[1];
        data[c++] = ((unsigned char *)&serviceId)[0];
        uint32_t methodId = request.GetMethodId();
        data[c++] = ((unsigned char *)&methodId)[3];
        data[c++] = ((unsigned char *)&methodId)[2];
        data[c++] = ((unsigned char *)&methodId)[1];
        data[c++] = ((unsigned char *)&methodId)[0];
        data[c++] = request.GetArgumentCount();
        for (unsigned int i = 0; i < request.GetArgumentCount(); i++) {
          if (request.GetArgumentLength(i) < 128) {
            data[c++] = request.GetArgumentLength(i);
          } else if (request.GetArgumentLength(i) < 256) {
            data[c++] = 0x81;
            data[c++] = request.GetArgumentLength(i);
          } else if (request.GetArgumentLength(i) < 256 * 256) {
            data[c++] = 0x82;
            data[c++] = request.GetArgumentLength(i) / 256;
            data[c++] = request.GetArgumentLength(i) % 256;
          } else if (request.GetArgumentLength(i) < 256 * 256 * 256) {
            data[c] = 0x83;
            data[c + 1] = request.GetArgumentLength(i) / (256 * 256);
            data[c + 2] = (request.GetArgumentLength(i) - data[c + 1] * 256 * 256) / 256;
            data[c + 3] = request.GetArgumentLength(i) % (256 * 256);
            c += 4;
          }
          unsigned char *argData = request.GetArgumentData(i);
          for (unsigned int j = 0; j < request.GetArgumentLength(i); j++) {
            data[c++] = argData[j];
          }
        }
        if (c != actualLength) {
          ::naeem::hottentot::runtime::Logger::GetError() << "Inconsistency in request serialization process." << std::endl;
          exit(1);
        }
        return data;
      }
      unsigned char* 
      ProtocolV1::SerializeResponse(Response &response, 
                                    uint32_t *length) {
        uint32_t actualLength = 0;
        actualLength += 1;  // Status Code
        if (response.GetDataLength() < 128) {
          actualLength += 1;
          actualLength += response.GetDataLength();
        } else if (response.GetDataLength() < 256) {
          actualLength += 2;
          actualLength += response.GetDataLength();
        } else if (response.GetDataLength() < 256 * 256) {
          actualLength += 3;
          actualLength += response.GetDataLength();
        } else if (response.GetDataLength() < 256 * 256 * 256) {
          actualLength += 4;
          actualLength += response.GetDataLength();
        }
        *length = actualLength;
        unsigned char *data = new unsigned char[*length];
        unsigned int c = 0;
        data[c++] = response.GetStatusCode();
        if (response.GetDataLength() < 128) {
          data[c++] = response.GetDataLength();
        } else if (response.GetDataLength() < 256) {
          data[c++] = 0x81;
          data[c++] = response.GetDataLength();
        } else if (response.GetDataLength() < 256 * 256) {
          data[c++] = 0x82;
          data[c++] = response.GetDataLength() / 256;
          data[c++] = response.GetDataLength() % 256;
        } else if (response.GetDataLength() < 256 * 256 * 256) {
          data[c] = 0x83;
          data[c + 1] = response.GetDataLength() / (256 * 256);
          data[c + 2] = (response.GetDataLength() - data[c + 1] * 256 * 256) / 256;
          data[c + 3] = response.GetDataLength() % (256 * 256);
          c += 4;
        }
        unsigned char *argData = response.GetData();
        for (uint32_t i = 0; i < response.GetDataLength(); i++) {
          data[c++] = argData[i];
        }
        return data;
      }
      Request* 
      ProtocolV1::DeserializeRequest(unsigned char  *data, 
                                     uint32_t       dataLength) {
        uint32_t c = 0;
        Request *request = new Request;
        request->SetType((Request::RequestType)data[c++]);
        if (::naeem::hottentot::runtime::Configuration::Verbose()) {
          ::naeem::hottentot::runtime::Logger::GetOut() << "Request Type: " << request->GetType() << std::endl;
        }
        uint32_t serviceId = 0;
        ((unsigned char *)(&serviceId))[3] = data[c++];
        ((unsigned char *)(&serviceId))[2] = data[c++];
        ((unsigned char *)(&serviceId))[1] = data[c++];
        ((unsigned char *)(&serviceId))[0] = data[c++];
        request->SetServiceId(serviceId);
        if (::naeem::hottentot::runtime::Configuration::Verbose()) {
          ::naeem::hottentot::runtime::Logger::GetOut() << "Service Id: " << serviceId << std::endl;
        }
        uint32_t methodId = 0;
        ((unsigned char *)(&methodId))[3] = data[c++];
        ((unsigned char *)(&methodId))[2] = data[c++];
        ((unsigned char *)(&methodId))[1] = data[c++];
        ((unsigned char *)(&methodId))[0] = data[c++];
        request->SetMethodId(methodId);
        if (::naeem::hottentot::runtime::Configuration::Verbose()) {
          ::naeem::hottentot::runtime::Logger::GetOut() << "Method Id: " << methodId << std::endl;
        }
        uint8_t argCount = data[c++];
        if (::naeem::hottentot::runtime::Configuration::Verbose()) {
          ::naeem::hottentot::runtime::Logger::GetOut() << "Arg. Count: " << (uint8_t)argCount << std::endl;
        }
        for (unsigned int k = 0; k < (uint8_t)argCount; k++) {
          if (data[c] == 0x00) {
            request->AddArgument(0, 0);
            if (::naeem::hottentot::runtime::Configuration::Verbose()) {
              ::naeem::hottentot::runtime::Logger::GetOut() << "Argument[" << k << "] Length: " << 0 << std::endl;
              ::naeem::hottentot::runtime::Logger::GetOut() << "Argument has zero length." << std::endl;
            }
          } else {
            uint32_t argLength = 0;
            if ((data[c] & 0x80) == 0) {
              argLength = data[c];
              c++;
            } else if (data[c] == 0x81) {
              argLength = data[c + 1];
              c += 2;
            } else if (data[c] == 0x82) {
              argLength = data[c + 1] * 256 + data[c + 2];
              c += 3;
            } else if (data[c] == 0x83) {
              argLength = data[c + 1] * 256 * 256 + data[c + 2] * 256 + data[c + 3];
              c += 4;
            }
            unsigned char *argData = new unsigned char[argLength];
            for (uint32_t i = 0; i < argLength; i++) {
              argData[i] = data[c++];
            }
            if (::naeem::hottentot::runtime::Configuration::Verbose()) {
              ::naeem::hottentot::runtime::Logger::GetOut() << "Argument[" << k << "] Length: " << argLength << std::endl;
              ::naeem::hottentot::runtime::Utils::PrintArray("Argument Data", argData, argLength);
            }
            request->AddArgument(argData, argLength);
          }
        }
        return request;
      }
      Response* 
      ProtocolV1::DeserializeResponse(unsigned char *data, 
                                      uint32_t       dataLength) {
        Response *response = new Response;
        uint32_t c = 0;
        response->SetStatusCode(data[c++]);
        uint32_t resultLength = 0;
        if (data[c] == 0x00) {
          response->SetData(0);
          response->SetDataLength(0);
          if (::naeem::hottentot::runtime::Configuration::Verbose()) {
            ::naeem::hottentot::runtime::Logger::GetOut() << "Response has zero length." << std::endl;
          }
          return response;
        } else {
          if ((data[c] & 0x80) == 0) {
            resultLength = data[c];
            c++;
          } else if (data[c] == 0x81) {
            resultLength = data[c + 1];
            c += 2;
          } else if (data[c] == 0x82) {
            resultLength = data[c + 1] * 256 + data[c + 2];
            c += 3;
          } else if (data[c] == 0x83) {
            resultLength = data[c + 1] * 256 * 256 + data[c + 2] * 256 + data[c + 3];
            c += 4;
          }
          unsigned char *resultData = new unsigned char[resultLength];
          for (uint32_t i = 0; i < resultLength; i++) {
            resultData[i] = data[c++];
          }
          response->SetData(resultData);
          response->SetDataLength(resultLength);
          if (::naeem::hottentot::runtime::Configuration::Verbose()) {
            ::naeem::hottentot::runtime::Utils::PrintArray("Response", resultData, resultLength);
          }
        }
        return response;
      }
      void 
      ProtocolV1::ProcessDataForRequest(unsigned char *data,
                                        uint32_t       dataLength) {
        if (::naeem::hottentot::runtime::Configuration::Verbose()) {
          ::naeem::hottentot::runtime::Logger::GetOut() << "We have data with length " << dataLength << " Bytes." << std::endl;
        }
        for (unsigned int i = 0; i < dataLength;) {
          if (currentState_ == ReadingLengthState) {
            if (readingCounter_ == 0) {
              readingBuffer_.clear();
              if ((data[i] & 0x80) == 0) {
                readingLength_ = data[i];
                readingCounter_ = 0;
                currentState_ = ReadingDataState;
                if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                  ::naeem::hottentot::runtime::Logger::GetOut() << "Request length is " << readingLength_ << " Bytes." << std::endl;
                }
              } else {
                targetCounter_ = (data[i] & 0x0f);
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
                if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                  ::naeem::hottentot::runtime::Logger::GetOut() << "Length is more than 127." << std::endl;
                }
              }
            } else {
              if (readingCounter_ <= targetCounter_) {
                // Gathering length bytes
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
              } else {
                uint32_t temp = 1;
                readingLength_ = 0;
                for (unsigned int c = targetCounter_; c > 0; c--) {
                  readingLength_ += readingBuffer_[c] * temp;
                  temp *= 256;
                }
                readingBuffer_.clear();
                readingCounter_ = 0;
                currentState_ = ReadingDataState;
                if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                  ::naeem::hottentot::runtime::Logger::GetOut() << "Request length is " << readingLength_ << " Bytes." << std::endl;
                }
                // Variable 'i' shouldn't get incremented because no byte is processed here.
                i--;
              }
            }
          } else if (currentState_ == ReadingDataState) {
            if (readingCounter_ == 0) {
              readingBuffer_.clear();
              readingBuffer_.push_back(data[i]);
              readingCounter_++;
              // ::naeem::hottentot::runtime::Logger::GetOut() << ">>>>> " << readingCounter_ << " from " << targetCounter_ << " : " << (unsigned int)data[i] << std::endl;
              targetCounter_ = readingLength_;
              if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                ::naeem::hottentot::runtime::Logger::GetOut() << "Preparing for reading the request body ..." << std::endl;
              }
            } else {
              if (readingCounter_ < targetCounter_) {
                // ::naeem::hottentot::runtime::Logger::GetOut() << "Reading request body : 0x" << std::hex << std::setfill('0') << std::setw(2) << (int)data[i] << " ..." << std::dec << std::endl;
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
                // ::naeem::hottentot::runtime::Logger::GetOut() << ">>>>> " << readingCounter_ << " from " << targetCounter_ << " : " << (unsigned int)data[i] << std::endl;
                if (readingCounter_ == targetCounter_) {
                  if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                    ::naeem::hottentot::runtime::Logger::GetOut() << "We have read " << readingCounter_ << " Bytes of request body ..." << std::endl;
                  }
                  uint32_t requestLength = readingLength_;
                  unsigned char *requestData = new unsigned char[requestLength];
                  for (unsigned int c = 0; c < requestLength; c++) {
                    requestData[c] = readingBuffer_[c];
                  }
                  readingBuffer_.clear();
                  readingCounter_ = 0;
                  currentState_ = ReadingLengthState;
                  // Request deserialization
                  if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                    ::naeem::hottentot::runtime::Logger::GetOut() << "Deserializing request ..." << std::endl;
                  }
                  Request *request = DeserializeRequest(requestData, requestLength);
                  if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                    ::naeem::hottentot::runtime::Logger::GetOut() << "Deserialized." << std::endl;
                  }
                  
                  if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                    ::naeem::hottentot::runtime::Logger::GetOut() << "Calling callback ..." << std::endl;
                  }
                  Response *response = requestCallback_->OnRequest(this, *request);
                  if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                    ::naeem::hottentot::runtime::Logger::GetOut() << "Callback was successful." << std::endl;
                  }
                  if (response) {
                    uint32_t responseSerializedLength = 0;
                    unsigned char *responseSerializedData = SerializeResponse(*response, &responseSerializedLength);
                    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                      ::naeem::hottentot::runtime::Utils::PrintArray("Serialized response: ", responseSerializedData, responseSerializedLength);
                    }
                    uint32_t sendLength = 0;
                    if (responseSerializedLength < 128) {
                      sendLength = 1 + responseSerializedLength;
                    } else if (responseSerializedLength < 256) {
                      sendLength = 2 + responseSerializedLength;
                    } else if (responseSerializedLength < 256 * 256) {
                      sendLength = 3 + responseSerializedLength;
                    } else if (responseSerializedLength < 256 * 256 * 256) {
                      sendLength = 4 + responseSerializedLength;
                    }
                    unsigned char *sendData = new unsigned char[sendLength];
                    uint32_t c = 0;
                    if (responseSerializedLength < 128) {
                      sendData[c++] = responseSerializedLength;
                    } else if (responseSerializedLength < 256) {
                      sendData[c++] = 0x81;
                      sendData[c++] = responseSerializedLength;
                    } else if (responseSerializedLength < 256 * 256) {
                      sendData[c++] = 0x82;
                      sendData[c++] = responseSerializedLength / 256;
                      sendData[c++] = responseSerializedLength % 256;
                    } else if (responseSerializedLength < 256 * 256 * 256) {
                      sendData[c] = 0x83;
                      sendData[c + 1] = responseSerializedLength / (256 * 256);
                      sendData[c + 2] = (responseSerializedLength - sendData[c + 1] * 256 * 256) / 256;
                      sendData[c + 3] = responseSerializedLength % (256 * 256);
                      c += 4;
                    }
                    for (unsigned int k = 0; k < responseSerializedLength; k++) {
                      sendData[c++] = responseSerializedData[k];
                    }
                    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                      ::naeem::hottentot::runtime::Utils::PrintArray("Response2", sendData, sendLength);
                    }
#ifndef _MSC_VER
                    write(remoteSocketFD_, sendData, sendLength * sizeof(unsigned char));
#else
                    send(remoteSocketFD_, (char *)sendData, sendLength * sizeof(unsigned char), 0);
#endif
                    delete [] sendData;
                    delete [] responseSerializedData;
                    delete response;
                  } else {
                    ::naeem::hottentot::runtime::Logger::GetError() << "No handler is found." << std::endl;
                  }
                  delete request;
                  delete [] requestData;
                }
              }
            }
          }
          i++;
        }
      }
      void 
      ProtocolV1::ProcessDataForResponse(unsigned char *data,
                                         uint32_t       dataLength) {
        for (unsigned int i = 0; i < dataLength;) {
          if (currentState_ == ReadingLengthState) {
            if (readingCounter_ == 0) {
              if ((data[i] & 0x80) == 0) {
                isResponseComplete_ = false;
                readingLength_ = data[i];
                readingCounter_ = 0;
                currentState_ = ReadingDataState;
                if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                  ::naeem::hottentot::runtime::Logger::GetOut() << "Response length is " << readingLength_ << " Bytes." << std::endl;
                }
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
                if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                  ::naeem::hottentot::runtime::Logger::GetOut() << "Response length is " << readingLength_ << " Bytes." << std::endl;
                }
                // Variable 'i' shouldn't get incremented because no byte is processed here.
                i--;
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
                if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                  // ::naeem::hottentot::runtime::Logger::GetOut() << "Reading response body : 0x" << std::hex << std::setfill('0') << std::setw(2) << (int)data[i] << " ..." << std::dec << std::endl;
                }
                readingBuffer_.push_back(data[i]);
                readingCounter_++;
                if (readingCounter_ == targetCounter_) {
                  uint32_t responseLength = readingLength_;
                  unsigned char *responseData = new unsigned char[responseLength];
                  for (unsigned int c = 0; c < responseLength; c++) {
                    responseData[c] = readingBuffer_[c];
                  }
                  if (::naeem::hottentot::runtime::Configuration::Verbose()) {
                    ::naeem::hottentot::runtime::Utils::PrintArray("Response", responseData, responseLength);
                  }
                  response_ = DeserializeResponse(responseData, responseLength);
                  readingBuffer_.clear();
                  readingCounter_ = 0;
                  currentState_ = ReadingLengthState;
                  isResponseComplete_ = true;
                  delete [] responseData;
                }
              }
            }
          }
          i++;
        }
      }
    }
  }
}