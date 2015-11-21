package example.runtime.factory;

import example.runtime.DefaultTcpServer;
import example.runtime.RequestHandler;
import example.runtime.TcpServer;

import java.util.Map;


public class TcpServerFactory {
    public static TcpServer create(String host , int port , Map<Integer , RequestHandler> requestHandlers) {
        return new DefaultTcpServer(host,port,requestHandlers);
    }
}
