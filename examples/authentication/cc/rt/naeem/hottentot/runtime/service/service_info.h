#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_INFO_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_INFO_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class ServiceInfo {
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
          inline Service* GetService() const {
            return service_;
          }
          inline void SetService(Service *service) {
            service_ = service;
          }
        private:
          std::string host_;
          uint32_t port_;
          Service *service_;
        };
      }
    }
  }
}



#endif

