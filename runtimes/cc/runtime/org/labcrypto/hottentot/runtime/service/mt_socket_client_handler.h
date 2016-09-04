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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_SERVICE__MT_SOCKET_CLIENT_HANDLER_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_SERVICE__MT_SOCKET_CLIENT_HANDLER_H_

#include "socket_client_handler.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace service {
  class RequestHandler;
  class MTSocketClientHandler : public SocketClientHandler {
  public:
    MTSocketClientHandler(
#ifndef _MSC_VER
      int clientSocketFD
#else
      SOCKET clientSocketFD
#endif
    ) : SocketClientHandler(clientSocketFD) {
    }
    virtual ~MTSocketClientHandler() {
    }
    private:
#ifdef _MSC_VER
    static DWORD WINAPI HandleClientConnection(LPVOID);
#else
    static void* HandleClientConnection(void *);
#endif
  public:
    virtual void Handle();
  };
  class _HandleClientThreadParams {
  public:
    MTSocketClientHandler *clientHandler_;
    int clientSocketFD_;
  };
}
}
}
}
}

#endif