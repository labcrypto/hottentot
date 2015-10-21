#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/request_writer.h>
#include <naeem/hottentot/runtime/tcp_client.h>
#include <naeem/hottentot/runtime/response.h>
#include <naeem/hottentot/runtime/response_reader.h>
#include <naeem/hottentot/runtime/default_tcp_client.h>

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
            request.SetType(::naeem::hottentot::runtime::Request::InvokeStateless);
            request.SetServiceId(1);
            request.SetMethodId(1);
            request.SetArgumentCount(1);
            request.SetType(::naeem::hottentot::runtime::Request::InvokeStateless);
            request.AddArgument(credentialSerializedData, 
                                credentialSerializedDataLength);
            // Connect to server
            ::naeem::hottentot::runtime::TcpClient *tcpClient = 
              new ::naeem::hottentot::runtime::DefaultTcpClient(); // TODO(kamran) Use factory.
            tcpClient->Connect(host_, port_);
            // Write the request object
            ::naeem::hottentot::runtime::RequestWriter requestWriter(tcpClient);
            requestWriter.WriteRequest(&request);
            ::naeem::hottentot::runtime::ResponseReader responseReader(tcpClient);
            ::naeem::hottentot::runtime::Response *response = responseReader.ReadResponse();
            // TODO(kamran) Deserialize token part of response
            Token *token = NULL;
            // Finalization
            tcpClient->Close();
            delete tcpClient;
            // TODO(kamran) Return token
            return token;
          }
        }
      }
    }
  }
}