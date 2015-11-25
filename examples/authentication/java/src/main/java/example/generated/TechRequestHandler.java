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

package ir.ntnaeem.hottentot.examples.tech;

import ir.ntnaeem.hottentot.runtime.Argument;
import ir.ntnaeem.hottentot.runtime.Request;
import ir.ntnaeem.hottentot.runtime.RequestHandler;
import ir.ntnaeem.hottentot.runtime.Response;
import ir.ntnaeem.hottentot.runtime.Service;
import ir.ntnaeem.hottentot.runtime.exception.MethodNotSupportException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import java.util.List;

public class TechRequestHandler extends RequestHandler {
    public TechRequestHandler(Service service) {
        super(service);
    }
    @Override
    public Response handleRequest(Request request) throws TcpClientWriteException, TcpClientReadException, TcpClientConnectException, MethodNotSupportException {
        byte methodId = request.getMethodId();
        TechService techImpl = (AbstractTechService) service;

	    if(methodId == 1){
            List <Argument> args = request.getArgs();
            Argument arg0 = args.get(0);
            byte[] serializedstring = arg0.getData();
            string message = new string();
            message.deserialize(serializedstring);
            void –oid = null;
            Response response = new Response();
            –oid = techImpl.report(message);
            byte[] serializedvoid = –oid.serialize();
            response.setStatusCode((byte) 100);
            response.setData(serializedvoid);
            response.setLength(serializedvoid.length + 1);
            return response;
        }if(methodId == 1){
            List <Argument> args = request.getArgs();
            int16 ‰nt16 = null;
            Response response = new Response();
            ‰nt16 = techImpl.getSerial();
            byte[] serializedint16 = ‰nt16.serialize();
            response.setStatusCode((byte) 100);
            response.setData(serializedint16);
            response.setLength(serializedint16.length + 1);
            return response;
        }
        throw new MethodNotSupportException("method id is incorrect");
    }
}
