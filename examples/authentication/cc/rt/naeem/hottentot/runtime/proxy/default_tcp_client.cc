#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>

#include "default_tcp_client.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        DefaultTcpClient::DefaultTcpClient(std::string host,
                                           uint32_t port)
            : TcpClient(host, port),
              socketFD_(0) {
        }
        DefaultTcpClient::~DefaultTcpClient() {
        }
        void 
        DefaultTcpClient::Connect() {
          struct sockaddr_in serverAddr;
          struct hostent *server;
          socketFD_ = socket(AF_INET, SOCK_STREAM, 0);
          if (socketFD_ < 0) {
            std::cerr << "ERROR opening socket" << std::endl;
            exit(1);
          }
          server = gethostbyname(host_.c_str());
          if (server == NULL) {
            std::cerr << "ERROR, no such host" << std::endl;
            exit(1);
          }
          memset((char *) &serverAddr, 0, sizeof(serverAddr));
          serverAddr.sin_family = AF_INET;
          bcopy((char *)&serverAddr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
          serverAddr.sin_port = htons(port_);
          if (connect(socketFD_, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "ERROR connecting" << std::endl;
          }
        }
        void 
        DefaultTcpClient::Write(unsigned char *data,
                                uint32_t       dataLength) {
          write(socketFD_, data, dataLength * sizeof(unsigned char));
        }
        uint32_t 
        DefaultTcpClient::Read(unsigned char *buffer,
                               uint32_t bufferLength) {
          return read(socketFD_, buffer, bufferLength * sizeof(unsigned char));
        }
        void 
        DefaultTcpClient::Close() {
          if (socketFD_ > 0) {
            close(socketFD_);
            socketFD_ = 0;
          }
        }
      }
    }
  }
}