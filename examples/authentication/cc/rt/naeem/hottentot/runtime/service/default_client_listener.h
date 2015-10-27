#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_CLIENT_LISTENER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_CLIENT_LISTENER_H_

#include <stdint.h>

#include "client_listener.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class DefaultClientListener : public ClientListener {
        public:
          virtual void OnNewClient(::naeem::hottentot::runtime::service::ClientSession *     /* Client session */);
          virtual void OnNewRequest(::naeem::hottentot::runtime::service::ClientSession *    /* Client session */,
                                    unsigned char *                                          /* Request data */, 
                                    uint32_t                                                 /* Request data length */);
          virtual void OnClientGone(::naeem::hottentot::runtime::service::ClientSession *    /* Client session */);
        };
      }
    }
  }
}

#endif
