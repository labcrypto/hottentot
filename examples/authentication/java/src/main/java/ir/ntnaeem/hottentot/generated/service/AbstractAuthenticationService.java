package ir.ntnaeem.hottentot.generated.service;

import ir.ntnaeem.hottentot.generated.AuthenticationRequestHandler;
import ir.ntnaeem.hottentot.generated.AuthenticationService;
import ir.ntnaeem.hottentot.runtime.RequestHandler;


public abstract class AbstractAuthenticationService implements AuthenticationService{

    public RequestHandler makeRequestHandler(){
        return new AuthenticationRequestHandler(this);
    }
    public  int getServiceId(){
        return 1;
    }
}
