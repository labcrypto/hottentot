package example.runtime.factory;

import example.runtime.DefaultTcpClient;
import example.runtime.TcpClient;


public class TcpClientFactory {

    public static TcpClient create(){
        return new DefaultTcpClient();
    }
}
