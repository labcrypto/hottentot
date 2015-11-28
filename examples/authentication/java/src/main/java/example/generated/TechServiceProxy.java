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
import ir.ntnaeem.hottentot.runtime.Proxy;
import ir.ntnaeem.hottentot.runtime.Request;
import ir.ntnaeem.hottentot.runtime.Response;
import ir.ntnaeem.hottentot.runtime.TcpClient;
import ir.ntnaeem.hottentot.runtime.exception.HottentotRuntimeException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import ir.ntnaeem.hottentot.runtime.factory.ProtocolFactory;
import ir.ntnaeem.hottentot.runtime.factory.TcpClientFactory;
import ir.ntnaeem.hottentot.runtime.protocol.Protocol;

public class TechServiceProxy extends AbstractTechService implements Proxy {
	
	private String host;
	private int port;

	public TechServiceProxy(String host, int port) {
		this.host = host;
		this.port = port;
	}
	public void report(string message) { 
        //serialize message
        byte[] serializedstring = message.serialize();

        //make request
        Request request = new Request();
        request.setServiceId((byte) 1);
        request.setMethodId((byte) 1);
        request.setArgumentCount((byte) 1);
        request.setType(Request.RequestType.InvokeStateless);
        Argument arg0 = new Argument();
        arg0.setDataLength(message.serialize().length);
        arg0.setData(message.serialize());
        request.addArgument(arg0);
        int dataLength = 0;
        //calculate data length for every argument
        //calulate messageDataLength
        int messageDataLength= serializedstring.length;
        int messageDataLengthByteArrayLength = 1;
        if (messageDataLength >= 0x80) {
            if (messageDataLength <= 0xff) {
                //ex 0x81 0xff
                messageDataLengthByteArrayLength = 2;
            } else if (messageDataLength <= 0xffff) {
                //ex 0x82 0xff 0xff
                messageDataLengthByteArrayLength = 3;
            } else if (messageDataLength <= 0xffffff) {
                //ex 0x83 0xff 0xff 0xff
                messageDataLengthByteArrayLength = 4;
            }
        }
        dataLength += messageDataLength + messageDataLengthByteArrayLength;
        //
        request.setLength(4 + dataLength);
        //connect to server
        TcpClient tcpClient = TcpClientFactory.create();
        try{
            tcpClient.connect(host, port);
        } catch (TcpClientConnectException e) {
            throw new HottentotRuntimeException(e);
        }
        //serialize request according to HTNP
        Protocol protocol = ProtocolFactory.create();
        byte[] serializedRequest = protocol.serializeRequest(request);
        //send request
        try {
            tcpClient.write(serializedRequest);
        } catch (TcpClientWriteException e) {
            throw new HottentotRuntimeException(e);
        }
        //read response from server
        byte[] buffer = new byte[256];
        while (!protocol.IsResponseComplete()) {
            byte[] dataChunkRead;
            try {
                dataChunkRead = tcpClient.read();
            } catch (TcpClientReadException e) {
                throw new HottentotRuntimeException(e);
            }
            protocol.processDataForResponse(dataChunkRead);
        }
        //deserialize token part of response
        Response response = protocol.getResponse();
        //close everything
        //deserialize voidpart from response
        void –oid= null;
        if (response.getStatusCode() == -1) {
            //
        } else {
            –oid= new void();
            –oid.deserialize(response.getData());
        }
        return –oid;
    }
public int16 getSerial() { 

        //make request
        Request request = new Request();
        request.setServiceId((byte) 1);
        request.setMethodId((byte) 1);
        request.setArgumentCount((byte) 0);
        request.setType(Request.RequestType.InvokeStateless);
        int dataLength = 0;
        //calculate data length for every argument
        //
        request.setLength(4 + dataLength);
        //connect to server
        TcpClient tcpClient = TcpClientFactory.create();
        try{
            tcpClient.connect(host, port);
        } catch (TcpClientConnectException e) {
            throw new HottentotRuntimeException(e);
        }
        //serialize request according to HTNP
        Protocol protocol = ProtocolFactory.create();
        byte[] serializedRequest = protocol.serializeRequest(request);
        //send request
        try {
            tcpClient.write(serializedRequest);
        } catch (TcpClientWriteException e) {
            throw new HottentotRuntimeException(e);
        }
        //read response from server
        byte[] buffer = new byte[256];
        while (!protocol.IsResponseComplete()) {
            byte[] dataChunkRead;
            try {
                dataChunkRead = tcpClient.read();
            } catch (TcpClientReadException e) {
                throw new HottentotRuntimeException(e);
            }
            protocol.processDataForResponse(dataChunkRead);
        }
        //deserialize token part of response
        Response response = protocol.getResponse();
        //close everything
        //deserialize int16part from response
        int16 ‰nt16= null;
        if (response.getStatusCode() == -1) {
            //
        } else {
            ‰nt16= new int16();
            ‰nt16.deserialize(response.getData());
        }
        return ‰nt16;
    }

	public void destroy() {
        	//TODO
	}
}
