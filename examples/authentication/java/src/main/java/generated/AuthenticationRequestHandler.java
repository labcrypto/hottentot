package generated;


import generated.service.AbstractAuthenticationService;
import runtime.Request;
import runtime.RequestHandler;
import runtime.Response;
import runtime.Service;
import java.util.List;


public class AuthenticationRequestHandler extends RequestHandler {
    public AuthenticationRequestHandler(Service service) {
        super(service);
    }
    @Override
    public Response handleRequest(Request request)  {
        System.out.println(request);
        byte methodId = request.getMethodId();
        AuthenticationService authenticationImpl = (AbstractAuthenticationService) service;
        System.out.println(authenticationImpl);
        if(methodId == 1){
            List<Argument> args = request.getArgs();
            Argument arg0 = args.get(0);
            byte[] serializedCredential = arg0.getData();
            Credential credential = new Credential();
            credential.deserialize(serializedCredential);
            Token token = null;
            Response response = new Response();
            try {
                token = authenticationImpl.authenticate(credential);
                byte[] serializedToken = token.serialize();
                response.setStatusCode((byte) 100);
                response.setData(serializedToken);
                response.setResponseLength(serializedToken.length + 2);

            } catch (Exception e) {
                e.printStackTrace();
            }
            System.out.println(response);

            return response;
        }
        //TODO throw exception
        return null;
    }
}
