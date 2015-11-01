package server;


import generated.Credential;
import generated.Token;
import generated.service.AbstractAuthenticationService;


public class AuthenticationImpl extends AbstractAuthenticationService{
    public Token authenticate(Credential credential){
        Token token = new Token();
        token.setValue("test");
        return token;
    }
}
