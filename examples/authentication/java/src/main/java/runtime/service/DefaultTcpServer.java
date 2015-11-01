package runtime.service;


import runtime.Endpoint;
import runtime.Protocol;
import runtime.RequestHandler;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;
import java.util.Map;

public class DefaultTcpServer implements TcpServer{

    private Protocol protocol;
    private int port;
    private String host;
    private Map<Integer ,RequestHandler> requestHandlers;

    public DefaultTcpServer(String host , int port , Map<Integer , RequestHandler> requestHandlers) {

    }

    public void bindAndStart() {
        //TODO
        //open server socket
        //accept socket
        try {
            ServerSocket serverSocket = new ServerSocket(port);
            Socket acceptSocket = serverSocket.accept();
            InputStream is = acceptSocket.getInputStream();
            //TODO i dont know how many bytes should I have to read
            byte[] readBytes = new byte[1];
            readBytes[0] = (byte) is.read();
            //TODO ASK KAMRAN !!!!
            protocol.processDataForRequest(readBytes);
        } catch (IOException e) {
            //TODO
            e.printStackTrace();
        }

    }

    public void setProtocol(Protocol protocol) {
        this.protocol = protocol;
    }
}
