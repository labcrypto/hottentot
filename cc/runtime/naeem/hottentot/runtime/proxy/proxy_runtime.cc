/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
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

#ifndef _MSC_VER
#include <signal.h>
#include <unistd.h>
#endif
 
#include "proxy_runtime.h"
#include "tcp_client.h"
#include "tcp_client_factory.h"
#include "default_tcp_client_factory.h"

#include "../configuration.h"


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        TcpClientFactory* ProxyRuntime::tcpClientFactory_ = 0;
        bool ProxyRuntime::initialized_ = false;
        void
        ProxyRuntime::Init(int argc,
                           char **argv) {
          if (initialized_) {
            return;
          }
          Configuration::Init(argc, argv);
#ifndef _MSC_VER
          signal(SIGPIPE, SIG_IGN);
#endif
          ProxyRuntime::initialized_ = true;
        }
        void
        ProxyRuntime::Shutdown() {
          if (!initialized_) {
            return;
          }
          if (tcpClientFactory_) {
            delete tcpClientFactory_;
          }
          initialized_ = false;
        }
        TcpClientFactory*
        ProxyRuntime::GetTcpClientFactory() {
          if (tcpClientFactory_ == 0) {
            tcpClientFactory_ = new DefaultTcpClientFactory;
          }
          return tcpClientFactory_;
        }
      }
    }
  }
}