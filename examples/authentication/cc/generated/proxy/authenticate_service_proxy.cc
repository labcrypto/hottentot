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

#include <iostream>

#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/utils.h>
#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/response.h>
#include <naeem/hottentot/runtime/protocol_v1.h>
#include <naeem/hottentot/runtime/proxy/tcp_client.h>
#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>
#include <naeem/hottentot/runtime/proxy/tcp_client_factory.h>

#include "authenticate_service_proxy.h"
#include "../token.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        namespace proxy {
          Token*
          AuthenticateServiceProxy::Authenticate(::naeem::hottentot::examples::auth::Credential *credential) {
            /*
             * Serialize credential object
             */
            uint32_t credentialSerializedDataLength = 0;
            ::naeem::hottentot::runtime::Logger::GetOut() << "Serializing credential ..." << std::endl;
            unsigned char *credentialSerializedData = credential->Serialize(&credentialSerializedDataLength);
            ::naeem::hottentot::runtime::Logger::GetOut() << "Credential serialized." << std::endl;
            /*
             * Make request object
             */
            ::naeem::hottentot::runtime::Logger::GetOut() << "Making request object ..." << std::endl;
            ::naeem::hottentot::runtime::Request request;
            request.SetServiceId(1);
            request.SetMethodId(1);
            request.SetArgumentCount(1);
            request.SetType(::naeem::hottentot::runtime::Request::InvokeStateless);
            request.AddArgument(credentialSerializedData, 
                                credentialSerializedDataLength);
            ::naeem::hottentot::runtime::Logger::GetOut() << "Request object is created." << std::endl;
            /*
             * Connect to server
             */
            ::naeem::hottentot::runtime::Logger::GetOut() << "Connecting to server " << host_ << ":" << port_ << " ..." << std::endl;
            ::naeem::hottentot::runtime::proxy::TcpClient *tcpClient = 
              ::naeem::hottentot::runtime::proxy::ProxyRuntime::GetTcpClientFactory()->CreateTcpClient(host_, port_);
            tcpClient->Connect();
            ::naeem::hottentot::runtime::Logger::GetOut() << "Connected." << std::endl;
            /*
             * Serialize request according to HOTP
             */
            ::naeem::hottentot::runtime::Protocol *protocol = 
              new ::naeem::hottentot::runtime::ProtocolV1(tcpClient->GetRemoteSocketFD()); // TODO(kamran): Use factory.
            uint32_t requestSerializedDataLength = 0;
            ::naeem::hottentot::runtime::Logger::GetOut() << "Serializing request object ..." << std::endl;
            unsigned char *requestSerializedData = protocol->SerializeRequest(request, 
                                                                              &requestSerializedDataLength);
            ::naeem::hottentot::runtime::Logger::GetOut() << "Request object is serialized." << std::endl;
            /*
             * Send request byte array
             */
            uint32_t sendLength = (requestSerializedDataLength > 127 ? 3 : 1) + requestSerializedDataLength;
            unsigned char *sendData = new unsigned char[sendLength];
            uint32_t c = 0;
            if (requestSerializedDataLength > 127) {
              sendData[c++] = 0x82;
              sendData[c++] = requestSerializedDataLength / 256;
              sendData[c++] = requestSerializedDataLength % 256;
            } else {
              sendData[c++] = requestSerializedDataLength;
            }
            for (uint32_t i = 0; i < requestSerializedDataLength; i++) {
              sendData[c++] = requestSerializedData[i];
            }
            ::naeem::hottentot::runtime::Logger::GetOut() << "Writing " << sendLength << "  Bytes to socket ..." << std::endl;
            ::naeem::hottentot::runtime::Utils::PrintArray("To Write", sendData, sendLength);
            tcpClient->Write(sendData, sendLength);
            ::naeem::hottentot::runtime::Logger::GetOut() << "Written." << std::endl;
            delete sendData;
            delete requestSerializedData;
            /*
             * Read response from server
             */
            ::naeem::hottentot::runtime::Logger::GetOut() << "Waiting for response ..." << std::endl;
            unsigned char buffer[256];
            while (!protocol->IsResponseComplete()) {
              int numOfReadBytes = tcpClient->Read(buffer, 256);
              protocol->ProcessDataForResponse(buffer, numOfReadBytes);
            }
            /*
             * Deserialize token
             */
            Token *token = new Token;
            ::naeem::hottentot::runtime::Utils::PrintArray("Response", protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
            token->Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
            /*
             * Finalization
             */
            tcpClient->Close();
            delete credentialSerializedData;
            delete protocol;
            delete tcpClient;
            /*
             * Return the acquired token
             */
            return token;
          }
        }
      }
    }
  }
}
