#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/response.h>
#include <naeem/hottentot/runtime/proxy/request_writer.h>
#include <naeem/hottentot/runtime/proxy/tcp_client.h>
#include <naeem/hottentot/runtime/proxy/response_reader.h>
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
            // Serialize credential object
            uint32_t credentialSerializedDataLength = 0;
            unsigned char *credentialSerializedData = credential->Serialize(&credentialSerializedDataLength);
            // Make request object
            ::naeem::hottentot::runtime::Request request;
            request.SetServiceId(1);
            request.SetMethodId(1);
            request.SetArgumentCount(1);
            request.SetType(::naeem::hottentot::runtime::Request::InvokeStateless);
            request.AddArgument(credentialSerializedData, 
                                credentialSerializedDataLength);
            // Connect to server
            ::naeem::hottentot::runtime::proxy::TcpClient *tcpClient = 
              ::naeem::hottentot::runtime::proxy::ProxyRuntime::GetTcpClientFactory()->CreateTcpClient(host_, port_);
            tcpClient->Connect();
            // Write the request object
            // Serialize request according to HTNP
            ::naeem::hottentot::runtime::Protocol *protocol = 
              new ::naeem::hottentot::runtime::ProtocolV1(); // TODO(kamran): Use factory.
            uint32_t requestSerializedDataLength = 0;
            unsigned char *requestSerilaizedData = protocol->SerializeRequest(request, 
                                                                              &requestSerializedDataLength);
            // Send request byte array
            tcpClient->Write(requestSerilaizedData, requestSerializedDataLength);
            
            unsigned char buffer[256];
            bool ok = true;
            while (ok) {
              int numOfReadBytes = tcpClient_->Read(buffer, 256);
              protocol->ProcessDataForResponse(buffer, numOfReadBytes);
              if (protocol->IsResponseComplete()) {
                ok = false;
              }
            }
            // ::naeem::hottentot::runtime::proxy::RequestWriter requestWriter(tcpClient);
            // requestWriter.WriteRequest(&request);
            // ::naeem::hottentot::runtime::proxy::ResponseReader responseReader(tcpClient);
            // ::naeem::hottentot::runtime::Response *response = responseReader.ReadResponse();
            // TODO(kamran) Deserialize token part of response
            Token *token = NULL;
            // Finalization
            tcpClient->Close();
            delete tcpClient;
            // Return token
            return token;
          }
        }
      }
    }
  }
}