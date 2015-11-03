#ifndef _NAEEM_HOTTENTOT_RUNTIME__UTILS_H_
#define _NAEEM_HOTTENTOT_RUNTIME__UTILS_H_

#include <iostream>
#include <iomanip>
#include <stdint.h>

#include "logger.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class Utils {
      public:
        static void PrintArray(std::string label,
                               unsigned char *buffer, 
                               uint32_t length) {
          Logger::GetOut() << label << ":" << std::endl;
          bool newLineInserted = false;
          for (uint32_t i = 0; i < length; i++) {
            newLineInserted = false;
            Logger::GetOut() << std::uppercase << std::hex << "0x" << 
              std::setw(2) << std::setfill ('0') << (unsigned int)buffer[i] << " ";
            if ((i + 1) % 8 == 0) {
              Logger::GetOut() << std::endl;
              newLineInserted = true;
            }
          }
          if (!newLineInserted) {
            Logger::GetOut() << std::endl;
          }
          Logger::GetOut() << std::dec;
        }
      };
    }
  }
}

#endif