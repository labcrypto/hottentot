package ir.ntnaeem.hottentot.runtime.factory;

import ir.ntnaeem.hottentot.runtime.DefaultTcpClient;
import ir.ntnaeem.hottentot.runtime.TcpClient;


public class TcpClientFactory {

    public static TcpClient create(){
        return new DefaultTcpClient();
    }
}
