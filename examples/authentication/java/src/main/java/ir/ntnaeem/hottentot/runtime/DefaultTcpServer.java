package ir.ntnaeem.hottentot.runtime;


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

public class DefaultTcpServer implements TcpServer {



    private int port;
    private String host;
    private Map<Integer, RequestHandler> requestHandlers;

    public DefaultTcpServer(String host, int port, Map<Integer, RequestHandler> requestHandlers) {
        this.requestHandlers = requestHandlers;
        this.host = host;
        this.port = port;
    }

    public void bindAndStart() throws IOException {
        //TODO write a multi thread approach
        //open ir.ntnaeem.hottentot.server socket
        //accept socket

        ServerSocket serverSocket = new ServerSocket(port);

        class ClientHandler implements Runnable, ResponseCallback {
            private Socket clientSocket;

            public ClientHandler(Socket clientSocket) {
                this.clientSocket = clientSocket;
            }

            public void run() {
                //receive data
                System.out.println("new thread ...");
                byte[] buffer = new byte[256];
                InputStream is = null;
                try {
                    is = clientSocket.getInputStream();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                int numReadBytes = 0;
                try {
                    numReadBytes = is.read(buffer, 0, buffer.length);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                System.out.println("number : " + numReadBytes);
                byte[] readDataChunk;
                Protocol protocol = ProtocolFactory.create();
                RequestCallback requestCallback = RequestCallbackFactory.create(requestHandlers);
                protocol.setRequestCallback(requestCallback);
                protocol.setResponseCallback(this);
                if (numReadBytes < 256) {
                    readDataChunk = Arrays.copyOf(buffer, numReadBytes);
                    System.out.println(Arrays.toString(readDataChunk));
                    protocol.processDataForRequest(readDataChunk);
                } else {
                    protocol.processDataForRequest(buffer);
                }
            }

            public void onResponse(byte[] serializedResponse) throws IOException {
                OutputStream os = clientSocket.getOutputStream();
                os.write(serializedResponse , 0 ,serializedResponse.length);
            }
        }
        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(new ClientHandler(clientSocket)).start();
        }

    }


}
