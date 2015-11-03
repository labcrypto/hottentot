package generated.proxy;


import generated.AuthenticationService;

public class AuthenticationServiceProxyBuilder {

    public static AuthenticationService create(String host, int port) {
        return new AuthenticationServiceProxy(host,port);
    }

    public static void destroy() {
        //TODO
    }
}
