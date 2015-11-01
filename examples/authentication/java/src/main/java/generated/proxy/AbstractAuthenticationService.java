package generated.proxy;

import generated.AuthenticationRequestHandler;
import generated.AuthenticationService;
import runtime.RequestHandler;
import runtime.Service;


abstract  class AbstractAuthenticationService implements Service, AuthenticationService {

    public RequestHandler makeRequestHandler(){
        return new AuthenticationRequestHandler();
    }
    public int getServiceId() {
        return 1;
    }


}
