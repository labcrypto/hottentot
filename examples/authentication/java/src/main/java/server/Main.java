package server;

import runtime.Service;
import runtime.ServiceRuntime;


public class Main {
    public static void main(String[] args) {
        Service authenticationService = new AuthenticationImpl();
        ServiceRuntime serviceRuntime = new ServiceRuntime();
        serviceRuntime.register("127.0.0.1",8000,authenticationService);
        serviceRuntime.start();
    }
}
