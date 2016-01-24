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


import ir.ntnaeem.hottentot.runtime.exception.HottentotRuntimeException;
import ir.ntnaeem.hottentot.runtime.exception.ProtocolProcessException;
import ir.ntnaeem.hottentot.runtime.exception.TcpServerReadException;
import ir.ntnaeem.hottentot.runtime.factory.ProtocolFactory;
import ir.ntnaeem.hottentot.runtime.factory.RequestCallbackFactory;
import ir.ntnaeem.hottentot.runtime.protocol.Protocol;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class DefaultTcpServer implements TcpServer {


  private int port;
  private ExecutorService executor;
  private String host;
  private final int THREAD_POOL_SIZE = 1000;
  private Map<Long, RequestHandler> requestHandlers;

  public DefaultTcpServer(String host, int port, Map<Long, RequestHandler> requestHandlers) {
    this.executor = Executors.newFixedThreadPool(THREAD_POOL_SIZE);
    this.requestHandlers = requestHandlers;
    this.host = host;
    this.port = port;
  }

  public void bindAndStart() throws IOException {
    ServerSocket serverSocket = new ServerSocket(port);
    class ClientHandler implements Runnable, ResponseCallback {
      private Socket clientSocket;
      private int tCounter;

      public ClientHandler(Socket clientSocket) {
        this.clientSocket = clientSocket;
      }

      public void run() {
        //receive data
        byte[] buffer = new byte[256];
        InputStream is = null;
        try {
          is = clientSocket.getInputStream();
        } catch (IOException e) {
          e.printStackTrace();
        }

        Protocol protocol = ProtocolFactory.create();
        RequestCallback requestCallback = RequestCallbackFactory.create(requestHandlers);
        protocol.setRequestCallback(requestCallback);
        protocol.setResponseCallback(this);

        while(!protocol.isRequestComplete()) {
          System.out.println("-----");
          int numReadBytes = 0;
          try {
            numReadBytes = is.read(buffer, 0, buffer.length);
            System.out.println("num read bytes : " + numReadBytes);
          } catch (IOException e) {
            e.printStackTrace();
          }
          byte[] readDataChunk;
          if (numReadBytes < 256) {
            try {
              readDataChunk = Arrays.copyOf(buffer, numReadBytes);
              protocol.processDataForRequest(readDataChunk);
            } catch (ProtocolProcessException e) {
              throw new HottentotRuntimeException(e);
            }
          } else {
            try {
              protocol.processDataForRequest(buffer);
            } catch (ProtocolProcessException e) {
              throw new HottentotRuntimeException(e);
            }
          }
        }

      }

      public void onResponse(byte[] serializedResponse) throws TcpServerReadException {
        OutputStream os = null;
        try {
          os = clientSocket.getOutputStream();
          os.write(serializedResponse, 0, serializedResponse.length);
        } catch (IOException e) {
          throw new TcpServerReadException();
        }
      }
    }

    while (true) {
      Socket clientSocket = serverSocket.accept();
      executor.execute(new ClientHandler(clientSocket));
      //executor.shutdown();
//          while (!executor.isTerminated()) {
//          }
      // new Thread(new ClientHandler(clientSocket)).start();
    }
  }


}
