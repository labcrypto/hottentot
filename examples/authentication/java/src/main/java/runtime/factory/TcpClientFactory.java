package runtime.factory;

import runtime.DefaultTcpClient;
import runtime.TcpClient;


public class TcpClientFactory {

    public static TcpClient create(){
        return new DefaultTcpClient();
    }
}
