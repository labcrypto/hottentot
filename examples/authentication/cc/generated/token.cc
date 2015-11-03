#include <iostream>
#include <string.h>

#include "token.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        unsigned char *
        Token::Serialize(uint32_t *length) {
          const char *valueString = value_.c_str();
          uint32_t actualLength = strlen(valueString) + 1;
          unsigned char *buffer = new unsigned char[actualLength];
          *length = actualLength;
          for (uint32_t i = 0; i < actualLength - 1; i++) {
            buffer[i] = value_[i];
          }
          buffer[actualLength - 1] = 0;
          return buffer;
        }
        void
        Token::Deserialize(unsigned char *data, 
                           uint32_t length) {
          SetValue((char *)data);
        }
      }
    }
  }
}