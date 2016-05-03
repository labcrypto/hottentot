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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__GC_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME__GC_H_

namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace service {
  class GC {
  public:
    GC() {}
    virtual ~GC() {
      Purge();
    }
  public:
    inline void LateDelete(void *pointer) {
      pointers_.push_back(pointer);
    }
    inline void LateDeleteArray(void *arrayPointer) {
      arrayPointers_.push_back(arrayPointer);
    }
    inline void Delete(void *pointer) {
      delete pointer;
    }
    inline void DeleteArray(void *arrayPointer) {
      delete [] arrayPointer;
    }
    inline virtual void Purge() {
      for (uint32_t i = 0; i < pointers_.size(); i++) {
        delete pointers_[i];
      }
      for (uint32_t i = 0; i < arrayPointers_.size(); i++) {
        delete [] arrayPointers_[i];
      }
    }
  private:
    std::vector<void*> voidPointers_;
    std::vector<void*> voidArrayPointers_;
  };
}
}
}
}
}

#endif