package generated.service;

import generated.AuthenticationRequestHandler;
import generated.AuthenticationService;
import runtime.RequestHandler;


public abstract class AbstractAuthenticationService implements AuthenticationService{

    public RequestHandler makeRequestHandler(){
        return new AuthenticationRequestHandler(this);
    }
    public  int getServiceId(){
        return 1;
    }
}
