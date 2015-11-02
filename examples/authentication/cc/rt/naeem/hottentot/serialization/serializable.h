#ifndef _NAEEM_HOTTENTOT_SERIALIZATION__SERIALIZABLE_H_
#define _NAEEM_HOTTENTOT_SERIALIZATION__SERIALIZABLE_H_

#include <stdint.h>
#include <vector>


namespace naeem {
  namespace hottentot {
    namespace serialization {
      class Serializable {
      public:
        virtual unsigned char * Serialize(uint32_t *        /* Pointer to length */) = 0;
        virtual Serializable* Deserialize(unsigned char *   /* Data */,
                                          uint32_t          /* Data length */) = 0;
      };
    }
  }
}

#endif