#include "credential.h"

namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        unsigned char *
        Credential::Serialize(uint32_t *length) {
          unsigned char *buffer = new unsigned char[10];
          *length = 10;
          for (uint32_t i = 0; i < *length; i++) {
            buffer[i] = 65 + i;
          }
          return buffer;
        }
        Credential*
        Credential::Deserialize(unsigned char *data, 
                                uint32_t length) {
          return NULL;
        }
      }
    }
  }
}