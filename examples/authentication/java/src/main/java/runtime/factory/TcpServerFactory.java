package runtime.factory;

import runtime.DefaultTcpServer;
import runtime.RequestHandler;
import runtime.TcpServer;

import java.util.Map;


public class TcpServerFactory {
    public static TcpServer create(String host , int port , Map<Integer , RequestHandler> requestHandlers) {
        return new DefaultTcpServer(host,port,requestHandlers);
    }
}
