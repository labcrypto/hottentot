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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT__LIST_H_
#define _ORG_LABCRYPTO_HOTTENTOT__LIST_H_

#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef _MSC_VER
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

#include "serializable.h"


namespace org {
namespace labcrypto {
namespace hottentot {
  template<class T>
  class List : public Serializable {
  public:
    List(){
    }
    virtual ~List() {
      /* for (uint32_t i = 0; i < elements_.size(); i++) {
        delete elements_[i];
      } */
    }
  public:
    inline void Add(T *e) {
      elements_.push_back(e);
    }
    inline T* Get(uint32_t i) {
      return elements_[i];
    }
    inline uint32_t Size() {
      return elements_.size();
    }
    inline void Purge() {
      typename std::vector<T*>::iterator it;
      for (it = elements_.begin(); it != elements_.end();) {
        delete *it;
        it = elements_.erase(it);
      }
    }
  public:
    inline virtual unsigned char * Serialize(uint32_t *length_ptr) {
      // std::cout << ">>>>>> " << elements_.size() << std::endl;
      std::vector<uint32_t> lengths;
      std::vector<unsigned char *> datas;
      for (uint32_t i = 0; i < elements_.size(); i++) {
        uint32_t eLength = 0;
        // std::cout << "Before Ser(" << i << ") ..." << std::endl;
        unsigned char *eData = elements_[i]->Serialize(&eLength);
        lengths.push_back(eLength);
        datas.push_back(eData);
        // std::cout << "Ser(" << i << ")" << std::endl;
      }
      uint32_t length = 0;
      for (uint32_t i = 0; i < lengths.size(); i++) {
        if (lengths[i] < 128) {
          length += 1 + lengths[i];
        } else if (lengths[i] < 256) {
          length += 2 + lengths[i];
        } else if (lengths[i] < 256 * 256) {
          length += 3 + lengths[i];
        } else if (lengths[i] < 256 * 256 * 256) {
          length += 4 + lengths[i];
        } /* else if (lengths[i] <= (256 * 256 * 256 * 256 - 1)) {
          length += 5 + lengths[i];
        } */
        // std::cout << "Len(" << i << ")" << std::endl;
      }
      uint32_t c = 0;
      unsigned char *data = new unsigned char[length];
      if (length_ptr) {
        *length_ptr = length;
      }
      for (uint32_t i = 0; i < lengths.size(); i++) {
        if (lengths[i] < 128) {
          data[c] = lengths[i];
          c += 1;
        } else if (lengths[i] < 256) {
          data[c] = 0x81;
          data[c + 1] = lengths[i];
          c += 2;
        } else if (lengths[i] < 256 * 256) {
          data[c] = 0x82;
          data[c + 1] = lengths[i] / 256;
          data[c + 2] = lengths[i] % 256;
          c += 3;
        } else if (lengths[i] < 256 * 256 * 256) {
          data[c] = 0x83;
          data[c + 1] = lengths[i] / (256 * 256);
          data[c + 2] = (lengths[i] - data[c + 1] * (256 * 256)) / 256;
          data[c + 3] = lengths[i] % (256 * 256);
          c += 4;
        } /* else if (lengths[i] <= (256 * 256 * 256 * 256 - 1)) {
          data[c] = 0x84;
          data[c + 1] = lengths[i] / (256 * 256 * 256);
          data[c + 2] = (lengths[i] - data[c + 1] * (256 * 256 * 256)) / (256 * 256);
          data[c + 3] = (lengths[i] - data[c + 1] * (256 * 256 * 256) - data[c + 2] * (256 * 256)) / 256;
          data[c + 4] = lengths[i] % (256 * 256 * 256);
          c += 5;
        } */
        for (uint32_t j = 0; j < lengths[i]; j++) {
          data[c++] = datas[i][j];
        }
        delete [] datas[i];
        // std::cout << "data(" << i << ")" << std::endl;
      }
      if (c != length) {
        std::cout << "List serialization: Inconsistency in serialized array length." << std::endl;
        exit(1);
      }
      return data;
    }
    inline virtual void Deserialize(unsigned char *data,
                                    uint32_t length) {
      if (length == 0) {
        return;
      }
      uint32_t i = 0;
      while (true) {
        uint32_t elength = 0;
        if ((data[i] & 0x80) == 0) {
          elength = data[i];
          i++;
        } else {
          uint32_t count = data[i] & 0x0f;
          i++;
          if (count == 1) {
            elength = data[i];
            i += 1;
          } else if (count == 2) {
            elength = data[i] * 256 + data[i + 1];
            i += 2;
          } else if (count == 3) {
            elength = data[i] * 256 * 256 + data[i + 1] * 256 + data[i + 2];
            i += 3;
          }
        }
        T *e = new T;
        // std::cout << "Length: " << elength << std::endl;
        e->Deserialize(data + i, elength);
        Add(e);
        i += elength;
        if (i >= length) {
          break;
        }
      }
    }
  private:
    std::vector<T*> elements_;
  };
}
}
}

#endif