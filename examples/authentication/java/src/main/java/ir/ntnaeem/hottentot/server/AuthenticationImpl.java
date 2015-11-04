package ir.ntnaeem.hottentot.server;


import ir.ntnaeem.hottentot.generated.Credential;
import ir.ntnaeem.hottentot.generated.Token;
import ir.ntnaeem.hottentot.generated.service.AbstractAuthenticationService;


public class AuthenticationImpl extends AbstractAuthenticationService{
    public Token authenticate(Credential credential){
        Token token = new Token();
        token.setValue("test");
        return token;
    }
}
