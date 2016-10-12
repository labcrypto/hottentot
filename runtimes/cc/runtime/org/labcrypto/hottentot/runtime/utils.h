/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__UTILS_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__UTILS_H_

#include <time.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#ifdef __WIN32__
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include "logger.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
  class Utils {
  public:
#ifdef __UNIX__
    static std::string GetCurrentUTCTimeString() {
      time_t     now = time(0);
      struct tm  tstruct;
      char       buffer[80];
      tstruct = *gmtime(&now);
      strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X UTC", &tstruct);
      return buffer;
    }
#else
    static std::string GetCurrentUTCTimeString(void) {
      time_t seconds_since_the_epoch;
      struct tm tm_struct;
      errno_t err;
      std::ostringstream buf;
      time(&seconds_since_the_epoch);
      if (seconds_since_the_epoch == -1) {
          return "";
      }
      err = gmtime_s(&tm_struct, &seconds_since_the_epoch);
      if (err) {
          return "";
      }
      buf
          <<        std::setw(4) << std::setfill('0') << tm_struct.tm_year + 1900
          << "-" << std::setw(2) << std::setfill('0') << tm_struct.tm_mon + 1
          << "-" << std::setw(2) << std::setfill('0') << tm_struct.tm_mday
          << "T" << std::setw(2) << std::setfill('0') << tm_struct.tm_hour
          << ":" << std::setw(2) << std::setfill('0') << tm_struct.tm_min
          << ":" << std::setw(2) << std::setfill('0') << tm_struct.tm_sec
          << "Z";
      return buf.str();
    }
#endif
    static void PrintArray(std::string label,
                           unsigned char *buffer, 
                           uint32_t length) {
      Logger::GetOut() << 
        "[" << GetCurrentUTCTimeString() << "]: " <<
          label << ":" << std::endl << "[" << GetCurrentUTCTimeString() << "]: ";
      bool newLineInserted = false;
      for (uint32_t i = 0; i < length; i++) {
        newLineInserted = false;
        Logger::GetOut() << 
          std::uppercase << std::hex << "0x" << 
            std::setw(2) << std::setfill ('0') << (unsigned int)buffer[i] << " ";
        if ((i + 1) % 8 == 0) {
          Logger::GetOut() << std::endl << "[" << GetCurrentUTCTimeString() << "]: ";
          newLineInserted = true;
        }
      }
      if (!newLineInserted) {
        Logger::GetOut() << std::endl << "[" << GetCurrentUTCTimeString() << "]: ";
      }
      Logger::GetOut() << std::dec;
    }
  };
}
}
}
}

#endif