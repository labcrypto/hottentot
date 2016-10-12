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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__STRING_HELPER_H_
#define _ORG_LABCRYPTO_HOTTENTOT_GENERATOR__STRING_HELPER_H_

#include <string>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>
#include <vector>
#include <stdexcept>

#include <stdio.h>
#include <string.h>
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


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
  class StringHelper {
  public:
    static inline bool StartsWith(std::string &str, 
                                  std::string &s) {
      const char *strCharArray = str.c_str();
      const char *sCharArray = s.c_str();
      return strncmp((char *)sCharArray, (char *)strCharArray, strlen(sCharArray)) == 0;
    } 
    static inline std::string& LeftTrim(std::string &s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
      return s;
    }
    static inline std::string& RightTrim(std::string &s) {
      s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
      return s;
    }
    static inline std::string& Trim(std::string &s) {
      return LeftTrim(RightTrim(s));
    }
    static inline std::string Replace(std::string s,
                                      const std::string toReplace,
                                      const std::string replaceWith) {
      std::string result = s;
      std::size_t index = result.find(toReplace);
      while (index != std::string::npos) {
        result = result.replace(index, toReplace.length(), replaceWith);
        index = result.find(toReplace);
      }
      return result;
    }
    static inline void Replace(std::string &s,
                               const std::string toReplace,
                               const std::string replaceWith,
                               uint32_t functionStatus) {
      if(functionStatus == 1){
        //std::string result = s;
        std::size_t index = s.find(toReplace);
        while (index != std::string::npos) {
          s.replace(index, toReplace.length(), replaceWith);
          index = s.find(toReplace);
        }
      }else{
        throw std::runtime_error("StringHelper::Replace : function status is not suppoerted.");
      }
    }
    static inline std::vector<std::string> Split(std::string str, 
                                                 char separator) {
      std::vector<std::string> tokens;
      std::istringstream f(str);
      std::string s;    
      while (getline(f, s, separator)) {
        tokens.push_back(s);
      }
      return tokens;
    }
    static inline std::string Concat(std::vector<std::string> strs, 
                                     std::string separator) {
      std::string result;
      std::string del = "";
      for (uint32_t i = 0; i < strs.size(); i++) {
        result += del + strs[i];
        del = separator;
      }
      return result;
    }
    static inline std::vector<std::string> ExplodeCamelCase(std::string str) {
      std::vector<std::string> tokens;
      uint32_t startIndex = 0;
      for (uint32_t i = 0; i < str.size(); i++) {
        if (i > 0 && str[i] >= 'A' && str[i] <= 'Z') {
          tokens.push_back(str.substr(startIndex, i - startIndex));
          startIndex = i;
        }
      }
      tokens.push_back(str.substr(startIndex, str.size() - startIndex));
      return tokens;
    }
    static inline std::string MakeLowerCase(std::string str) {
      std::string result(str);

      std::transform(str.begin(), str.end(), result.begin(), ::tolower);
      return result;
    }
    static inline std::string MakeUpperCase(std::string str) {
      std::string result(str);
      std::transform(str.begin(), str.end(), result.begin(), ::toupper);
      return result;
    }
    static inline std::string MakeFirstCapital(std::string str) {
      if((int)str[0] < 97 || (int)str[0] > 122){
        return str;   
      }    
      std::string result = str;
      result[0] = std::toupper(result[0]);
      return result;         
    }
    static inline std::string MakeFirstLowerCase(std::string str) {
      if((int)str[0] < 65 || (int)str[0] > 90){
        return str;   
      }    
      std::string result = str;
      result[0] = std::tolower(result[0]);
      return result;         
    }
    static inline std::string MakeCamelCase(std::vector<std::string> strs, 
                                            bool firstCapital = true) {
      std::stringstream ss;
      for (uint32_t i = 0; i < strs.size(); i++) {
        if (i == 0 && !firstCapital) {
          ss << MakeLowerCase(strs[i]);
        } else {
          ss << MakeFirstCapital(MakeLowerCase(strs[i]));
        }
      }
      return ss.str();
    }
    static inline std::string MakeSnakeCase(std::vector<std::string> strs) {
      std::stringstream ss;
      std::string del = "";
      for (uint32_t i = 0; i < strs.size(); i++) {
        ss << del << MakeLowerCase(strs[i]);
        del = "_";
      }
      return ss.str();
    }
    static inline std::string MakeScreamingSnakeCase(std::vector<std::string> strs) {
      std::stringstream ss;
      std::string del = "";
      for (uint32_t i = 0; i < strs.size(); i++) {
        ss << del << MakeUpperCase(strs[i]);
        del = "_";
      }
      return ss.str();
    }
    static inline std::string MakeCamelCaseFirstCapital(std::string str, 
                                                        char del = ' ') {
      return MakeCamelCase(Split(MakeSnakeCaseFromCamelCase(str), '_'));
    }
    static inline std::string MakeCamelCaseFirstSmall(std::string str, 
                                                      char del = ' ') {
      return MakeCamelCase(Split(MakeSnakeCaseFromCamelCase(str), '_'), false);
    }
    static inline std::string MakeSnakeCase(std::string str, 
                                            char del = ' ') {
      return MakeSnakeCase(Split(str, del));
    }
    static inline std::string MakeScreamingSnakeCase(std::string str, 
                                                     char del = ' ') {
      return MakeScreamingSnakeCase(Split(str, del));
    }
    static inline std::string MakeCamelCaseFirstCapitalFromSnakeCase(std::string str) {
      return MakeCamelCase(Split(str, '_'));
    }
    static inline std::string MakeCamelCaseFirstCapitalFromScreamingSnakeCase(std::string str) {
      return MakeCamelCase(Split(str, '_'));
    }
    static inline std::string MakeSnakeCaseFromCamelCase(std::string str) {
      return MakeSnakeCase(ExplodeCamelCase(str));
    }
    static inline std::string MakeSnakeCaseFromScreamingSnakeCase(std::string str) {
      return MakeSnakeCase(Split(str, '_'));
    }
    static inline std::string MakeScreamingSnakeCaseFromCamelCase(std::string str) {
      return MakeScreamingSnakeCase(ExplodeCamelCase(str));
    }
    static inline std::string MakeScreamingSnakeCaseFromSnakeCase(std::string str) {
      return MakeScreamingSnakeCase(Split(str, '_'));
    }
  };
}
}
}
}

#endif