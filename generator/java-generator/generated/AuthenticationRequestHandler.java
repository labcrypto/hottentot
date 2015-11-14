package ir.naeem.hottentot.generated;


import ir.naeem.hottentot.generated.AbstractAuthenticationService;
import ir.ntnaeem.hottentot.runtime.*;

import java.util.List;


public class AuthenticationRequestHandler extends RequestHandler {
    public AuthenticationRequestHandler(Service service) {
        super(service);
    }
    @Override
    public Response handleRequest(Request request)  {
        byte methodId = request.getMethodId();
        AuthenticationService authenticationImpl = (AbstractAuthenticationService) service;

	[%METHOD_CONDITIONS%]
        
        //TODO throw exception
        return null;
    }
}
