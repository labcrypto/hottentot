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

package ir.ntnaeem.hottentot.runtime;

import ir.ntnaeem.hottentot.runtime.config.Config;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientCloseException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Arrays;

public class DefaultTcpClient implements TcpClient {

    private Socket socket;
    private final int BUFFER_SIZE = 10;

    public void connect(String host, int port) throws TcpClientConnectException {
        //TODO
        try {
            socket = new Socket(host, port);
        } catch (IOException e) {
            throw new TcpClientConnectException(e);
        }
    }

    public void write(byte[] data) throws TcpClientWriteException {
        OutputStream os = null;
        try {
            os = socket.getOutputStream();
            os.write(data, 0, data.length);
        } catch (IOException e) {
            throw new TcpClientWriteException(e);
        }
    }

    public byte[] read() throws TcpClientReadException {
        //TODO
        InputStream is = null;
        byte[] buffer = new byte[256];
        try {
            is = socket.getInputStream();
            int numReadBytes = is.read(buffer, 0, buffer.length);
            if(numReadBytes < 256){
                byte[] readBytes = Arrays.copyOf(buffer, numReadBytes);
                return readBytes;
            }
            //byte b = (byte)is.read();
            //buffer[0] = b;
            return buffer;
        } catch (IOException e) {
            e.printStackTrace();
            throw new TcpClientReadException();
        }
    }

    public void close() throws TcpClientCloseException {
      try {
        if(Config.isVerboseMode){
          System.out.println("client has closed its socket");
        }
        socket.close();
      } catch (IOException e) {
        throw new TcpClientCloseException(e);
      }
    }
}
