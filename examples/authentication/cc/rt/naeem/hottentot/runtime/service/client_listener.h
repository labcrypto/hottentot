#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__CLIENT_LISTENER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__CLIENT_LISTENER_H_

namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class ClientListener {
          public:
            virtual void OnNewClient(::naeem::hottentot::runtime::service::ClientSession *     /* Client session */) = 0;
            virtual void OnNewMessage(::naeem::hottentot::runtime::service::ClientSession *    /* Client session */,
                                      unsigned char *                                          /* Message data */, 
                                      unsigned int                                             /* Message data length */) = 0;
            virtual void OnClientGone(::naeem::hottentot::runtime::service::ClientSession *    /* Client session */) = 0;
        };
      }
    }
  }
}



#endif
