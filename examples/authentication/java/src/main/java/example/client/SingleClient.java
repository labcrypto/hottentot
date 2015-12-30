package example.client;

import example.generated.AuthenticationService;
import example.generated.AuthenticationServiceProxyBuilder;
import example.generated.Credential;
import example.generated.Token;

import java.util.Arrays;


public class SingleClient {
  public static void main(String[] args) {
    final AuthenticationService proxy = AuthenticationServiceProxyBuilder.create("127.0.0.1", 8080);
    Credential credential = new Credential();
    credential.setUsername("zoro");
    credential.setPassword("12345");
    Token token = proxy.authenticate(credential);
    System.out.println(token.getValue());
    System.out.println(Arrays.toString(token.getSampleData()));
    AuthenticationServiceProxyBuilder.destroy();
  }
}
