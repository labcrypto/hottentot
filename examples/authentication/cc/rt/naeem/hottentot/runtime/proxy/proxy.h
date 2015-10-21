#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__PROXY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__PROXY_H_

namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class Proxy {
        public:
          Proxy(std::string host, uint32_t port)
            : host_(host), port_(port) {
          }
          ~Proxy() {}
        public:
          virtual void Destroy();
        protected:
          std::string host_;
          uint32_t port_;
        };
      }
    }
  }
}

#endif