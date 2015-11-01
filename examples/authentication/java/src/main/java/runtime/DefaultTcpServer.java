package runtime;


import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;

public class DefaultTcpServer implements TcpServer{


    private int port;
    private String host;
    private Map<Integer ,RequestHandler> requestHandlers;

    public DefaultTcpServer(String host , int port , Map<Integer , RequestHandler> requestHandlers) {
        this.requestHandlers = requestHandlers;
        this.host = host;
        this.port = port;
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
            //TODO(ali) what is buffer size !!!!

            //TODO(ali) use factory
            ProtocolV1 protocolV1 = new ProtocolV1();
            protocolV1.processDataForRequest(readBytes);
            RequestCallBack requestCallBack = new DefaultRequestCallback(requestHandlers);
        } catch (IOException e) {
            //TODO
            e.printStackTrace();
        }

    }

}
