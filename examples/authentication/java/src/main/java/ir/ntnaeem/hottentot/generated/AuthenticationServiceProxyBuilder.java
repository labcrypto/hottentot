package ir.ntnaeem.hottentot.generated;


public class AuthenticationServiceProxyBuilder {

    public static AuthenticationService create(String host, int port) {
        return new AuthenticationServiceProxy(host,port);
    }

    public static void destroy() {
        //TODO
    }
}
