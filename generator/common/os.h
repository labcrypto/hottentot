#ifndef _NAEEM_HOTTENTOT_GENERATOR__COMMON__OS_H_
#define _NAEEM_HOTTENTOT_GENERATOR__COMMON__OS_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include "string_helper.h"


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace common {
        class Os {
        public:
          static inline void MakeDir(std::string pathString) {
            std::string tPathString = StringHelper::trim(pathString);
            #ifdef _WIN32
              std::string adjPathString = StringHelper::replace(tPathString, "/", "\\");
              std::size_t index = adjPathString.find("/");
              while (index != std::string::npos) {
                if (index > 0) {
                  const char *path = adjPathString.substr(0, index).c_str();
                  wchar_t wpath[1024] = { 0 };
                  mbstowcs(wpath, path, strlen(path) + 1);
                  CreateDirectory(wpath, NULL);
                }
                index = adjPathString.find("/", index + 1);
              }
              const char *path = adjPathString.c_str();
              wchar_t wpath[1024] = { 0 };
              mbstowcs(wpath, path, strlen(path) + 1);
              CreateDirectory(wpath, NULL);
            #else
              std::string adjPathString = StringHelper::replace(tPathString, "\\", "/");
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
        };
      }
    }
  }
}

#endif