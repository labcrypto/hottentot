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
 
#include <stdlib.h>
#include <string.h>

#include "configuration.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
  bool Configuration::verbose_ = false;
  uint32_t Configuration::socketReadTimeout_ = 30;
  std::vector<std::string> Configuration::options_;
  std::map<std::string, std::string> Configuration::values_;
  void 
  Configuration::Init(int argc,
                      char **argv) {
    for (unsigned short i = 0; i < argc; i++) {
      if (strncmp(argv[i], "--", 2) == 0) {
        options_.push_back(argv[i] + 2);
      } else if (strncmp(argv[i], "-", 1) == 0) {
        options_.push_back(argv[i] + 1);
      } else {
        if (options_.size() > 0) {
          values_.insert(std::pair<std::string, std::string>(options_[options_.size() - 1], argv[i]));
        }
      }
      if (strncmp(argv[i], "-v", 2) == 0) {
        verbose_ = true;
      } else if (strncmp(argv[i], "--verbose", 9) == 0) {
        verbose_ = true;
      } else if (strncmp(argv[i], "--socket-read-timeout", 21) == 0) {
        socketReadTimeout_ = atoi(argv[i + 1]);
      }
    }
  }
  bool 
  Configuration::Exists(std::string optionShortName, std::string optionCompleteName) {
    for (uint32_t i = 0; i < options_.size(); i++) {
      if (options_[i] == optionShortName || options_[i] == optionCompleteName) {
        return true;
      }
    }
    return false;
  }
  bool
  Configuration::HasValue(std::string optionShortName, std::string optionCompleteName) {
    for (std::map<std::string, std::string>::iterator it = values_.begin();
         it != values_.end();
         it++) {
      if (it->first == optionShortName || it->first == optionCompleteName) {
        return true;
      }
    }
    return false;
  }
  uint32_t 
  Configuration::AsUInt32(std::string optionShortName, std::string optionCompleteName) {
    for (std::map<std::string, std::string>::iterator it = values_.begin();
         it != values_.end();
         it++) {
      if (it->first == optionShortName || it->first == optionCompleteName) {
        return atol(it->second.c_str());
      }
    }
    return 0;
  }
  uint64_t 
  Configuration::AsUInt64(std::string optionShortName, std::string optionCompleteName) {
    for (std::map<std::string, std::string>::iterator it = values_.begin();
         it != values_.end();
         it++) {
      if (it->first == optionShortName || it->first == optionCompleteName) {
#ifndef _MSC_VER
        return atoll(it->second.c_str());
#else
        return _atoi64(it->second.c_str());
#endif
      }
    }
    return 0;
  }
  std::string 
  Configuration::AsString(std::string optionShortName, std::string optionCompleteName) {
    for (std::map<std::string, std::string>::iterator it = values_.begin();
         it != values_.end();
         it++) {
      if (it->first == optionShortName || it->first == optionCompleteName) {
        return it->second.c_str();
      }
    }
    return "";
  }
}
}
}
}