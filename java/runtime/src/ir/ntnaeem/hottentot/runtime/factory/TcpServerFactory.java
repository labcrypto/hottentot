package ir.ntnaeem.hottentot.runtime.factory;

import ir.ntnaeem.hottentot.runtime.DefaultTcpServer;
import ir.ntnaeem.hottentot.runtime.RequestHandler;
import ir.ntnaeem.hottentot.runtime.TcpServer;
import java.util.Map;


public class TcpServerFactory {
    public static TcpServer create(String host , int port , Map<Integer , RequestHandler> requestHandlers) {
        return new DefaultTcpServer(host,port,requestHandlers);
    }
}
