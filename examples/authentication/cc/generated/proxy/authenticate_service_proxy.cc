#include <naeem/hottentot/runtime/request.h>

#include "authenticate_service_proxy.h"
#include "../token.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        namespace proxy {
          Token*
          AuthenticateServiceProxy::Authenticate(::naeem::hottentot::examples::auth::Credential *credential) {
            // TODO(kamran) Serialize credential object
            uint32_t credentialSerializedDataLength = 0;
            unsigned char *credentialSerializedData = credential->Serialize(&credentialSerializedDataLength);
            // TODO(kamran) Make request
            ::naeem::hottentot::runtime::Request request;
            request.SetType(::naeem::hottentot::runtime::RequestType::InvokeStateless);
            request.SetServiceId(1);
            request.SetMethodId(1);
            request.SetArgumentCount(1);
            request.SetType(::naeem::hottentot::runtime::RequestType::InvokeStateless);
            request.AddArgument(credentialSerializedData, 
                                credentialSerializedDataLength);
            // TODO(kamran) Serailize request according to HTNP
            ::naeem::hottentot::runtime::Protocol *protocol = 
              new ::naeem::hottentot::runtime::ProtocolV1(); // TODO(kamran) Use factory.
            uint32_t requestSerializedDataLength = 0;
            unsigned char *requestSerilaizedData = protocol->SerializeRequest(&request, 
                                                                              &requestSerializedDataLength);
            // TODO(kamran) Connect to server
            ::naeem::hottentot::runtime::TcpClient *tcpClient = 
              new ::naeem::hottentot::runtime::DefaultTcpClient(); // TODO(kamran) Use factory.
            tcpClient->Connect(host_, port_); // TODO(kamran) Provide host and port
            // TODO(kamran) Send request byte array
            tcpClient->WriteRequest(requestSerilaizedData, requestSerializedDataLength); // TODO(kamran): Move serialization to a new class named RequestWriter.
            // TODO(kamran) Read response byte array
            uint32_t responseSerializedDataLength = 0;
            unsigned char *responseSerializedData = tcpClient->ReadResponse(&responseSerializedDataLength);
            // TODO(kamran) Deserialize response byte array
            ::naeem::hottentot::runtime::Response *response = protocol->DeserializeResponse(responseSerializedData, 
                                                                                            responseSerializedDataLenght);
            // TODO(kamran) Deserialize token part of response
            // TODO(kamran) GC
            // TODO(kamran) Return token
            return NULL;
          }
        }
      }
    }
  }
}