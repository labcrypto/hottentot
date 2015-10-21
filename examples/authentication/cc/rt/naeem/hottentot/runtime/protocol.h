#ifndef _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_H_
#define _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_H_

#include <stdint.h>
#include <vector>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Protocol {
      public:
        virtual unsigned char* SerializeRequest(Request *    /* Request object*/, 
                                                uint32_t *   /* Length */) = 0;
      };
    }
  }
}

#endif