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

package example.generated;

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

public class CalculatorServiceProxy extends AbstractCalculatorService implements Proxy {
	
	private String host;
	private int port;

	public CalculatorServiceProxy(String host, int port) {
		this.host = host;
		this.port = port;
	}
	public uint32 add(uint32 a,,uint32 b) { 
        //serialize b
        byte[] serializeduint32 = b.serialize();
        //serialize b
        byte[] serializeduint32 = b.serialize();

        //make request
        Request request = new Request();
        request.setServiceId((byte) 1);
        request.setMethodId((byte) 1);
        request.setArgumentCount((byte) 2);
        request.setType(Request.RequestType.InvokeStateless);
        Argument arg0 = new Argument();
        arg0.setDataLength(a,.serialize().length);
        arg0.setData(a,.serialize());
        request.addArgument(arg0);
        Argument arg1 = new Argument();
        arg1.setDataLength(b.serialize().length);
        arg1.setData(b.serialize());
        request.addArgument(arg1);
        int dataLength = 0;
        //calculate data length for every argument
        //calulate a,DataLength
        int a,DataLength= serializeduint32.length;
        int a,DataLengthByteArrayLength = 1;
        if (a,DataLength >= 0x80) {
            if (a,DataLength <= 0xff) {
                //ex 0x81 0xff
                a,DataLengthByteArrayLength = 2;
            } else if (a,DataLength <= 0xffff) {
                //ex 0x82 0xff 0xff
                a,DataLengthByteArrayLength = 3;
            } else if (a,DataLength <= 0xffffff) {
                //ex 0x83 0xff 0xff 0xff
                a,DataLengthByteArrayLength = 4;
            }
        }
        dataLength += a,DataLength + a,DataLengthByteArrayLength;
        //calulate bDataLength
        int bDataLength= serializeduint32.length;
        int bDataLengthByteArrayLength = 1;
        if (bDataLength >= 0x80) {
            if (bDataLength <= 0xff) {
                //ex 0x81 0xff
                bDataLengthByteArrayLength = 2;
            } else if (bDataLength <= 0xffff) {
                //ex 0x82 0xff 0xff
                bDataLengthByteArrayLength = 3;
            } else if (bDataLength <= 0xffffff) {
                //ex 0x83 0xff 0xff 0xff
                bDataLengthByteArrayLength = 4;
            }
        }
        dataLength += bDataLength + bDataLengthByteArrayLength;
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
        //deserialize uint32part from response
        uint32 品nt32= null;
        if (response.getStatusCode() == -1) {
            //
        } else {
            品nt32= new uint32();
            品nt32.deserialize(response.getData());
        }
        return 品nt32;
    }

	public void destroy() {
        	//TODO
	}
}
