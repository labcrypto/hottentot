package ir.naeem.hottentot.generated.proxy;


import ir.naeem.hottentot.generated.AuthenticationService;

public class AuthenticationServiceProxyBuilder {

	public static AuthenticationService create(String host, int port) {
		return new AuthenticationServiceProxy(host,port);
	}

    	public static void destroy() {
        	//TODO
    	}
}
