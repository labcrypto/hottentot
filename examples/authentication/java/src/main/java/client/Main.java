package client;


import generated.AuthenticationService;
import generated.Credential;
import generated.Token;
import generated.proxy.AuthenticationServiceProxyBuilder;
import runtime.exception.TcpClientConnectException;
import runtime.exception.TcpClientReadException;
import runtime.exception.TcpClientWriteException;

public class Main {
    public static void main(String[] args) {
        AuthenticationService proxy = AuthenticationServiceProxyBuilder.create("127.0.0.1", 8000);
        Credential credential = new Credential();
        credential.setUsername("test");
        credential.setPassword("12345");
        try {
            Token token = proxy.authenticate(credential);
            System.out.println(token.getValue());
        } catch (TcpClientConnectException e) {
            e.printStackTrace();
        } catch (TcpClientWriteException e) {
            e.printStackTrace();
        } catch (TcpClientReadException e){
            e.printStackTrace();
        }
        AuthenticationServiceProxyBuilder.destroy();
    }
}
