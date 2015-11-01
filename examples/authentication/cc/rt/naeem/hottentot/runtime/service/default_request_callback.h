#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_REQUEST_CALLBACK_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__DEFAULT_REQUEST_CALLBACK_H_

#include "../request_callback.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class DefaultRequestCallback : public RequestCallback {
        public:
          virtual Response* OnRequest(void *     /* Source */,
                                      Request &  /* Request object */);
        };
      }
    }
  }
}

#endif