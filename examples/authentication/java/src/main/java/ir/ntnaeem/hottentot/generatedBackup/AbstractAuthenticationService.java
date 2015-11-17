package ir.ntnaeem.hottentot.generatedBackup;

import ir.ntnaeem.hottentot.runtime.RequestHandler;
import ir.ntnaeem.hottentot.runtime.Service;


public abstract class AbstractAuthenticationService implements AuthenticationService{

    public RequestHandler makeRequestHandler(){
        return new AuthenticationRequestHandler(this);
    }
    public  int getServiceId(){
        return 1;
    }
}
