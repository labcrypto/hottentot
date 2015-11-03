#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__REQUEST_HANDLER_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__REQUEST_HANDLER_H_


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Request;
      class Response;
      namespace service {
        class Service;
        class RequestHandler {
        public:
          RequestHandler(Service *service)
            : service_(service) {
          }
          virtual ~RequestHandler() {}
        public:
          virtual void HandleRequest(Request &   /* Request object */,
                                     Response &  /* Response object */) = 0;
        protected:
          Service* service_;
        };
      }
    }
  }
}

#endif