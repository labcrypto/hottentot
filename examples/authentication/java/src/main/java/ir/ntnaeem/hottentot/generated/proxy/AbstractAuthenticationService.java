package ir.ntnaeem.hottentot.generated.proxy;

import ir.ntnaeem.hottentot.generated.AuthenticationRequestHandler;
import ir.ntnaeem.hottentot.generated.AuthenticationService;
import ir.ntnaeem.hottentot.runtime.RequestHandler;
import ir.ntnaeem.hottentot.runtime.Service;


abstract class AbstractAuthenticationService implements Service, AuthenticationService {

    public RequestHandler makeRequestHandler(){
        return new AuthenticationRequestHandler(this);
    }
    public int getServiceId() {
        return 1;
    }
}
