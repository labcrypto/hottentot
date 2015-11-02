#ifndef _NAEEM_HOTTENTOT_RUNTIME__RESPONSE_H_
#define _NAEEM_HOTTENTOT_RUNTIME__RESPONSE_H_

#include <stdint.h>
#include <vector>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Response {
      private:
        /*
         * Success = 0
         * Fault = 500+
         */
        uint8_t statusCode_;
        unsigned char *data_;
        uint32_t dataLength_;
      };
    }
  }
}

#endif