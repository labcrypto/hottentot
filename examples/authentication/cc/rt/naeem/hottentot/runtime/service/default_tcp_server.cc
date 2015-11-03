#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <iostream>

#include "default_tcp_server.h"
#include "default_request_callback.h"
#include "../logger.h"
#include "../protocol_v1.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        DefaultTcpServer::DefaultTcpServer(std::string host,
                                           uint16_t port,
                                           std::map<uint8_t, RequestHandler*> *requestHandlers)
            : TcpServer(host, port, requestHandlers), 
              serverSocketFD_(-1) {
        }
        DefaultTcpServer::~DefaultTcpServer() {
        }
        void
        DefaultTcpServer::BindAndStart() {
          if (serverSocketFD_ < 0) {
            struct sockaddr_in servAddr;
            int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
            memset((char *) &servAddr, 0, sizeof(servAddr));
            servAddr.sin_family = AF_INET;
            servAddr.sin_addr.s_addr = INADDR_ANY;
            servAddr.sin_port = htons(port_);
            if (bind(serverSocketFD, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
              ::naeem::hottentot::runtime::Logger::GetError() << "Error on bind." << std::endl;
              exit(EXIT_FAILURE);
            }
            listen(serverSocketFD, 5);
            serverSocketFD_ = serverSocketFD;
            pthread_t thread;
            int ret = pthread_create(&thread, NULL, AcceptClients, (void *)this);
            if (ret) {
              ::naeem::hottentot::runtime::Logger::GetError() << "Error - pthread_create() return code: " << ret << std::endl;
              exit(EXIT_FAILURE);
            }
          }
        }
        void*
        DefaultTcpServer::AcceptClients(void *data) {
          bool ok = true;
          struct sockaddr_in clientAddr;
          socklen_t clientAddrLength = sizeof(clientAddr);
          DefaultTcpServer *ref = (DefaultTcpServer*)data;
          while (ok) {
            int clientSocketFD = accept(ref->serverSocketFD_, (struct sockaddr *) &clientAddr, &clientAddrLength);
            _HandleClientConnectionParams *params = new _HandleClientConnectionParams;
            params->tcpServer_ = ref;
            params->clientSocketFD_ = clientSocketFD;
            pthread_t thread; // TODO(kamran): We need a thread pool here.
            int ret = pthread_create(&thread, NULL, HandleClientConnection, (void *)params);
            if (ret) {
              ::naeem::hottentot::runtime::Logger::GetError() << "Error - pthread_create() return code: " << ret << std::endl;
              exit(EXIT_FAILURE);
            }
          }
        }
        void*
        DefaultTcpServer::HandleClientConnection(void *data) {
          bool ok = true;
          _HandleClientConnectionParams *ref = (_HandleClientConnectionParams*)data;
          unsigned char buffer[256];
          ::naeem::hottentot::runtime::Protocol *protocol = 
            new ::naeem::hottentot::runtime::ProtocolV1(ref->clientSocketFD_);
          DefaultRequestCallback *requestCallback = new DefaultRequestCallback(ref->tcpServer_->requestHandlers_);
          protocol->SetRequestCallback(requestCallback);
          while (ok) {            
            uint32_t numOfReadBytes = read(ref->clientSocketFD_, buffer, 256);
            if (numOfReadBytes <= 0) {
              ok = false;
            }
            if (ok) {
              protocol->ProcessDataForRequest(buffer, numOfReadBytes);
            }
          }
          close(ref->clientSocketFD_);
          delete protocol;
          delete ref;
        }
      }
    }
  }
}