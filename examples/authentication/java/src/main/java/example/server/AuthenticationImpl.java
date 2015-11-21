package example.server;


import example.generated.AbstractAuthenticationService;
import example.generated.Credential;
import example.generated.Token;


public class AuthenticationImpl extends AbstractAuthenticationService {
    public Token authenticate(Credential credential){
        Token token = new Token();
        token.setValue("test");
        return token;
    }
}
