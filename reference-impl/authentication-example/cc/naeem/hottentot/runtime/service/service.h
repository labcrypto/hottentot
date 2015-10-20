#ifndef _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_H_
#define _NAEEM_HOTTENTOT_RUNTIME_SERVICE__SERVICE_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace service {
        class Service {
        public:
          virtual uint8_t GetServiceId() const = 0;
        };
      }
    }
  }
}

#endif