#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/response.h>
#include <naeem/hottentot/runtime/protocol_v1.h>
#include <naeem/hottentot/runtime/proxy/request_writer.h>
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
            // Serialize request according to HTNP
            ::naeem::hottentot::runtime::Protocol *protocol = 
              new ::naeem::hottentot::runtime::ProtocolV1(); // TODO(kamran): Use factory.
            uint32_t requestSerializedDataLength = 0;
            unsigned char *requestSerilaizedData = protocol->SerializeRequest(request, 
                                                                              &requestSerializedDataLength);
            // Send request byte array
            tcpClient->Write(requestSerilaizedData, requestSerializedDataLength);
            // Read response from server
            unsigned char buffer[256];
            while (!protocol->IsResponseComplete()) {
              int numOfReadBytes = tcpClient->Read(buffer, 256);
              protocol->ProcessDataForResponse(buffer, numOfReadBytes);
            }
            // Deserialize token
            Token *token = new Token;
            token->Deserialize(protocol->GetResponse()->GetData(), protocol->GetResponse()->GetDataLength());
            // Finalization
            tcpClient->Close();
            delete protocol;
            delete tcpClient;
            // Return the aquired token
            return token;
          }
        }
      }
    }
  }
}