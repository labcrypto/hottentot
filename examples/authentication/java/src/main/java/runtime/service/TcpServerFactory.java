package runtime.service;

import runtime.RequestHandler;

import java.util.List;
import java.util.Map;


public class TcpServerFactory {
    public static TcpServer create(String host , int port , Map<Integer , RequestHandler> requestHandlers) {
        return new DefaultTcpServer(host,port,requestHandlers);
    }
}
