package ir.ntnaeem.hottentot.generated.proxy;


import ir.ntnaeem.hottentot.generated.AuthenticationService;

public class AuthenticationServiceProxyBuilder {

    public static AuthenticationService create(String host, int port) {
        return new AuthenticationServiceProxy(host,port);
    }

    public static void destroy() {
        //TODO
    }
}
