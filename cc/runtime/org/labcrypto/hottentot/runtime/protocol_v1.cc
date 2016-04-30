/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
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
#include <exception>
#include <stdexcept>
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


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
  ProtocolV1::ProtocolV1(int remoteSocketFD) 
    : Protocol(remoteSocketFD),
      isResponseComplete_(false),
      response_(0),
      readingLength_(0),
      readingCounter_(0),
      targetCounter_(0),
      currentState_(ReadingLengthState) {
  }
  ProtocolV1::~ProtocolV1() {
    if (response_) {
      delete response_;
    }
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
      ::org::labcrypto::hottentot::runtime::Logger::GetError() << 
        "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
          "Inconsistency in request serialization process." << std::endl;
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
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
          "Request Type: " << request->GetType() << std::endl;
    }
    uint32_t serviceId = 0;
    ((unsigned char *)(&serviceId))[3] = data[c++];
    ((unsigned char *)(&serviceId))[2] = data[c++];
    ((unsigned char *)(&serviceId))[1] = data[c++];
    ((unsigned char *)(&serviceId))[0] = data[c++];
    request->SetServiceId(serviceId);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
          "Service Id: " << serviceId << std::endl;
    }
    uint32_t methodId = 0;
    ((unsigned char *)(&methodId))[3] = data[c++];
    ((unsigned char *)(&methodId))[2] = data[c++];
    ((unsigned char *)(&methodId))[1] = data[c++];
    ((unsigned char *)(&methodId))[0] = data[c++];
    request->SetMethodId(methodId);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
          "Method Id: " << methodId << std::endl;
    }
    uint8_t argCount = data[c++];
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
          "Arg. Count: " << (uint8_t)argCount << std::endl;
    }
    for (unsigned int k = 0; k < (uint8_t)argCount; k++) {
      if (data[c] == 0x00) {
        request->AddArgument(0, 0);
        if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
          ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
            "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
              "Argument[" << k << "] Length: " << 0 << std::endl;
          ::org::labcrypto::hottentot::runtime::Logger::GetOut() <<  
            "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
              "Argument has zero length." << std::endl;
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
        if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
          ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
            "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
              "Argument[" << k << "] Length: " << argLength << std::endl;
          ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Argument Data", argData, argLength);
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
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
          "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
            "Response has zero length." << std::endl;
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
      if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
        ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Response", resultData, resultLength);
      }
    }
    return response;
  }
  void 
  ProtocolV1::ProcessDataForRequest(unsigned char *data,
                                    uint32_t       dataLength) {
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
        "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
          "We have data with length " << dataLength << " Bytes." << std::endl;
    }
    for (unsigned int i = 0; i < dataLength;) {
      if (currentState_ == ReadingLengthState) {
        if (readingCounter_ == 0) {
          readingBuffer_.clear();
          if ((data[i] & 0x80) == 0) {
            readingLength_ = data[i];
            readingCounter_ = 0;
            currentState_ = ReadingDataState;
            if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
              ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                "[" << Utils::GetCurrentUTCTimeString() << "]: " <<  
                  "Request length is " << readingLength_ << " Bytes." << std::endl;
            }
          } else {
            targetCounter_ = (data[i] & 0x0f);
            readingBuffer_.push_back(data[i]);
            readingCounter_++;
            if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
              ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                  "Length is more than 127." << std::endl;
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
            if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
              ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                  "Request length is " << readingLength_ << " Bytes." << std::endl;
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
          // ::org::labcrypto::hottentot::runtime::Logger::GetOut() << ">>>>> " << readingCounter_ << " from " << targetCounter_ << " : " << (unsigned int)data[i] << std::endl;
          targetCounter_ = readingLength_;
          if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
            ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
              "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                "Preparing for reading the request body ..." << std::endl;
          }
        } else {
          if (readingCounter_ < targetCounter_) {
            // ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "Reading request body : 0x" << std::hex << std::setfill('0') << std::setw(2) << (int)data[i] << " ..." << std::dec << std::endl;
            readingBuffer_.push_back(data[i]);
            readingCounter_++;
            // ::org::labcrypto::hottentot::runtime::Logger::GetOut() << ">>>>> " << readingCounter_ << " from " << targetCounter_ << " : " << (unsigned int)data[i] << std::endl;
            if (readingCounter_ == targetCounter_) {
              if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                  "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                    "We have read " << readingCounter_ << " Bytes of request body ..." << std::endl;
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
              if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                  "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                    "Deserializing request ..." << std::endl;
              }
              Request *request = DeserializeRequest(requestData, requestLength);
              if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                  "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                    "Deserialized." << std::endl;
              }
              
              if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                  "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                    "Calling callback ..." << std::endl;
              }
              Response *response = requestCallback_->OnRequest(this, *request);
              if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                  "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                    "Callback was successful." << std::endl;
              }
              if (response) {
                uint32_t responseSerializedLength = 0;
                unsigned char *responseSerializedData = SerializeResponse(*response, &responseSerializedLength);
                if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                  ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Serialized response: ", responseSerializedData, responseSerializedLength);
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
                if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                  ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Response2", sendData, sendLength);
                }
                if (sendLength > 0) {
}
#ifndef _MSC_VER
                  try {
                    int result = write(remoteSocketFD_, sendData, sendLength * sizeof(unsigned char));
                    if (result <= 0) {
                      throw std::runtime_error("[" + Utils::GetCurrentUTCTimeString() + "]: Write to proxy failed.");
                    }
                    /* for (uint32_t i = 0; i < sendLength; i++) {
                      std::cout << "Writing ..." << std::endl;
                      int result = write(remoteSocketFD_, &sendData[i], sizeof(unsigned char));
                      std::cout << "Write result: " << result << std::endl;
                      if (result <= 0) {
                        throw std::runtime_error("Write to proxy failed.");
                      }
                      sleep(2);
                    } */
#else
                  try {
                    int result = send(remoteSocketFD_, (char *)sendData, sendLength * sizeof(unsigned char), 0);
                    if (result == SOCKET_ERROR) {
                      throw std::runtime_error("[" + Utils::GetCurrentUTCTimeString() + "]: Write to proxy failed.");
                    }
#endif
                  } catch (std::exception &e) {
                    ::org::labcrypto::hottentot::runtime::Logger::GetError() <<
                      "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                         e.what() << std::endl;
                  }
                }
                delete [] sendData;
                delete [] responseSerializedData;
                delete response;
              } else {
                ::org::labcrypto::hottentot::runtime::Logger::GetError() << 
                  "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                    "No handler is found." << std::endl;
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
            if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
              ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                  "Response length is " << readingLength_ << " Bytes." << std::endl;
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
            if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
              ::org::labcrypto::hottentot::runtime::Logger::GetOut() << 
                "[" << Utils::GetCurrentUTCTimeString() << "]: " <<
                  "Response length is " << readingLength_ << " Bytes." << std::endl;
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
            if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
              // ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "Reading response body : 0x" << std::hex << std::setfill('0') << std::setw(2) << (int)data[i] << " ..." << std::dec << std::endl;
            }
            readingBuffer_.push_back(data[i]);
            readingCounter_++;
            if (readingCounter_ == targetCounter_) {
              uint32_t responseLength = readingLength_;
              unsigned char *responseData = new unsigned char[responseLength];
              for (unsigned int c = 0; c < responseLength; c++) {
                responseData[c] = readingBuffer_[c];
              }
              if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
                ::org::labcrypto::hottentot::runtime::Utils::PrintArray("Response", responseData, responseLength);
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
}