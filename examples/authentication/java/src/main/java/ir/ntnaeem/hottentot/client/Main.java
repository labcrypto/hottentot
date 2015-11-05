package ir.ntnaeem.hottentot.client;


import ir.ntnaeem.hottentot.generated.AuthenticationService;
import ir.ntnaeem.hottentot.generated.Credential;
import ir.ntnaeem.hottentot.generated.Token;
import ir.ntnaeem.hottentot.generated.proxy.AuthenticationServiceProxyBuilder;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;

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
