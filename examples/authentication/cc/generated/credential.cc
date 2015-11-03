#include <string.h>

#include "credential.h"


namespace naeem {
  namespace hottentot {
    namespace examples {
      namespace auth {
        unsigned char *
        Credential::Serialize(uint32_t *length) {
          const char *usernameString = username_.c_str();
          const char *passwordString = password_.c_str();
          uint32_t actualLength = 0;
          actualLength += 1; // 1 byte for length of username
          actualLength += strlen(usernameString) + 1; // Length of username
          actualLength += 1; // 1 byte for length of password
          actualLength += strlen(passwordString) + 1; // Length of password
          unsigned char *buffer = new unsigned char[actualLength];
          *length = actualLength;
          uint32_t c = 0;
          buffer[c++] = strlen(usernameString) + 1;
          for (uint32_t i = 0; i < strlen(usernameString); i++) {
            buffer[c++] = usernameString[i];
          }
          buffer[c++] = 0;
          buffer[c++] = strlen(passwordString) + 1;
          for (uint32_t i = 0; i < strlen(passwordString); i++) {
            buffer[c++] = passwordString[i];
          }
          buffer[c++] = 0;
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