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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTAB_STRILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
package org.labcrypto.hottentot.runtime;

import org.labcrypto.hottentot.runtime.exception.TcpClientConnectException;
import org.labcrypto.hottentot.runtime.exception.TcpClientReadException;
import org.labcrypto.hottentot.runtime.exception.TcpClientWriteException;

import java.util.Map;

public class DefaultRequestCallback implements RequestCallback {

  private Map<Long, RequestHandler> requestHandlers;

  public DefaultRequestCallback(Map<Long, RequestHandler> requestHandlers) {
    this.requestHandlers = requestHandlers;
  }

  public Response onRequest(Request request) throws TcpClientReadException, TcpClientConnectException, TcpClientWriteException {
    RequestHandler requestHandler = requestHandlers.get(request.getServiceId());
    return requestHandler.handleRequest(request);
  }
}
