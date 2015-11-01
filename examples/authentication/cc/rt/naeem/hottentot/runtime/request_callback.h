#ifndef _NAEEM_HOTTENTOT_RUNTIME__REQUEST_CALLBACK_H_
#define _NAEEM_HOTTENTOT_RUNTIME__REQUEST_CALLBACK_H_


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Request;
      class Response;
      class RequestCallback {
      public:
        virtual Response* OnRequest(void *     /* Source */,
                                    Request &  /* Request object */) = 0;
      };
    }
  }
}

#endif