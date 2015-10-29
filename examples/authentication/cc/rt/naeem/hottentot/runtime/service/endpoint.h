#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__ENDPOINT_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__ENDPOINT_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        // TODO(kamran) We need different endpoints for IPv4 and IPv6.
        class Endpoint {
        public:
          Endpoint(std::string host, uint32_t port) 
            : host_(host), port_(port) {
          }
          ~Endpoint() {}
        public:
          inline std::string GetHost() const {
            return host_;
          }
          inline void SetHost(std::string host) {
            host_ = host;
          }
          inline uint32_t GetPort() const {
            return port_;
          }
          inline void SetPort(uint32_t port) {
            port_ = port;
          }
          inline bool operator<(const Endpoint &e) const {
            return host_ < e.host_ && port_ < e.port_;
          }
        private:
          std::string host_;
          uint32_t port_;
        };
      }
    }
  }
}

#endif