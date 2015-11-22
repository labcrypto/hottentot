package example.server;

import ir.ntnaeem.hottentot.runtime.Service;
import ir.ntnaeem.hottentot.runtime.ServiceRuntime;
import java.io.IOException;

public class Main {
    public static void main(String[] args){
        Service authenticationService = new AuthenticationImpl();
        ServiceRuntime serviceRuntime = new ServiceRuntime();
        serviceRuntime.register("127.0.0.1",8000,authenticationService);
        serviceRuntime.start();
    }
}
