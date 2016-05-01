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

#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__OS_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__OS_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <string>
#include <stdlib.h>
#include <fstream>
#include <streambuf>
#include <stdexcept>

#include "string_helper.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
  class Os {
  public:
    static inline void MakeDir(std::string pathString) {
      std::string tPathString = StringHelper::Trim(pathString);
#ifdef _WIN32
        std::string adjPathString = StringHelper::Replace(tPathString, "/", "\\");
        std::size_t index = adjPathString.find("\\");
        while (index != std::string::npos) {
          if (index > 0) {
            std::string subs = adjPathString.substr(0, index);
            const char *path = subs.c_str();
            wchar_t wpath[1024] = { 0 };
            mbstowcs(wpath, path, strlen(path) + 1);
            CreateDirectory(wpath, NULL);                  
          }
          index = adjPathString.find("\\", index + 1);
        }
        const char *path = adjPathString.c_str();
        wchar_t wpath[1024] = { 0 };
        mbstowcs(wpath, path, strlen(path) + 1);
        CreateDirectory(wpath, NULL);              
#else
        std::string adjPathString = StringHelper::Replace(tPathString, "\\", "/");
        std::size_t index = adjPathString.find("/");
        while (index != std::string::npos) {
          if (index > 0) {
            const char *path = adjPathString.substr(0, index).c_str();
            struct stat st = {0};
            if (stat(path, &st) == -1) {
              mkdir(path, 0700);
            }
          }
          index = adjPathString.find("/", index + 1);
        }
        const char *path = adjPathString.c_str();
        struct stat st = {0};
        if (stat(path, &st) == -1) {
          mkdir(path, 0700);
        }
#endif
    }
    static inline void ReadFile(std::string path, std::string &content) {
      std::ifstream t(path.c_str());
      if (t.fail()) {
        throw std::runtime_error("File couldn't be opened.");
      }
      t.seekg(0, std::ios::end);   
      content.reserve(t.tellg());
      t.seekg(0, std::ios::beg);
      content.assign((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());
    }
    static inline void WriteFile(std::string path , std::string &content){
      std::ofstream os;
      os.open(path.c_str() , std::ios::trunc);
      if (os.fail()) {
        throw std::runtime_error("File couldn't be opened.");
      }
      os.write(content.c_str() , content.size());
      os.close();
    }
  };
}
}
}
}

#endif