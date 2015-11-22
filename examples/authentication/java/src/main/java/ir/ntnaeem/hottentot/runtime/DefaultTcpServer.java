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
        ServerSocket serverSocket = new ServerSocket(port);
        class ClientHandler implements Runnable, ResponseCallback {
            private Socket clientSocket;
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
                int numReadBytes = 0;
                try {
                    numReadBytes = is.read(buffer, 0, buffer.length);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                byte[] readDataChunk;
                Protocol protocol = ProtocolFactory.create();
                RequestCallback requestCallback = RequestCallbackFactory.create(requestHandlers);
                protocol.setRequestCallback(requestCallback);
                protocol.setResponseCallback(this);
                if (numReadBytes < 256) {
                    readDataChunk = Arrays.copyOf(buffer, numReadBytes);
                    try {
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

            public void onResponse(byte[] serializedResponse) throws TcpServerReadException{
                OutputStream os = null;
                try {
                    os = clientSocket.getOutputStream();
                    os.write(serializedResponse, 0, serializedResponse.length);
                }
                catch (IOException e) {
                    throw new TcpServerReadException();
                }
            }
        }
        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(new ClientHandler(clientSocket)).start();
        }

    }


}
