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


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        DefaultTcpServer::DefaultTcpServer(std::string host,
                                           uint16_t port,
                                           std::vector<Service*> *services)
            : TcpServer(host, port, services), serverSocketFD_(-1) {
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
              std::cerr << "ERROR on binding" << std::endl;
              exit(EXIT_FAILURE);
            }
            listen(serverSocketFD, 5);
            serverSocketFD_ = serverSocketFD;
            pthread_t thread;
            int ret = pthread_create(&thread, NULL, AcceptClients, (void *)this);
            if (ret) {
              fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);
              exit(EXIT_FAILURE);
            }
            // pthread_join(thread, NULL);
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
            std::cout << "Client is connected." << std::endl;
            close(clientSocketFD);
          }
        }
      }
    }
  }
}