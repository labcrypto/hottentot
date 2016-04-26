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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_FACTORY_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_FACTORY_H_

#include "tcp_client_factory.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class DefaultTcpClientFactory : public TcpClientFactory {
        public:
          virtual ~DefaultTcpClientFactory() {}
        public:
          virtual TcpClient* CreateTcpClient(std::string           /* Host */,
                                             uint32_t              /* Port */);
        };
      }
    }
  }
}

#endif