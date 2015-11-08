/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

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
        void
        Credential::Deserialize(unsigned char *data, 
                                uint32_t length) {
          // TODO(kamran)
        }
      }
    }
  }
}