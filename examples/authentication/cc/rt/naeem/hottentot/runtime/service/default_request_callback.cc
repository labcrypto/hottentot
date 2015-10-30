#include "default_request_callback.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        Response*
        DefaultRequestCallback::OnRequest(void *source,
                                          Request &request) {
          return 0;
        }
      }
    }
  }
}