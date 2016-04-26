/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Organization
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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_V1_H_
#define _NAEEM_HOTTENTOT_RUNTIME__PROTOCOL_V1_H_

#include <vector>

#include "protocol.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      class ProtocolV1 : public Protocol {
      enum State {
        ReadingLengthState,
        ReadingDataState
      };
      public:
        ProtocolV1(int /* Remote Socket FD */);
        virtual ~ProtocolV1();
      public:
        virtual unsigned char* SerializeRequest(Request &      /* Request object*/, 
                                                uint32_t *     /* Length */);
        virtual unsigned char* SerializeResponse(Response &    /* Response object*/, 
                                                 uint32_t *    /* Length */);
        virtual Request* DeserializeRequest(unsigned char *   /* Request data */, 
                                             uint32_t          /* Request data length */);
        virtual Response* DeserializeResponse(unsigned char *  /* Response data */, 
                                              uint32_t         /* Response data length */);
      public:
        virtual void ProcessDataForRequest(unsigned char *     /* Data chuck */,
                                           uint32_t            /* Data chunk length */);
        virtual void ProcessDataForResponse(unsigned char *    /* Data chuck */,
                                            uint32_t           /* Data chunk length */);
      public:
        virtual bool IsResponseComplete();
        virtual Response* GetResponse();
      private:
        bool isResponseComplete_;
        Response *response_;
      private:
        uint32_t readingLength_;
        uint32_t readingCounter_;
        uint32_t targetCounter_;
        std::vector<unsigned char> readingBuffer_;
        State currentState_;
      };
    }
  }
}

#endif