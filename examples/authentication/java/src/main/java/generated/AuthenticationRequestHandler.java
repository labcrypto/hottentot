package generated;

import runtime.Argument;
import runtime.Request;
import runtime.RequestHandler;
import runtime.Response;
import server.AuthenticationImpl;

import java.util.List;


public class AuthenticationRequestHandler implements RequestHandler {

    public Response handleRequest(Request request) {
        byte methodId = request.getMethodId();
        AuthenticationImpl authenticationImpl = new AuthenticationImpl();
        Response response = new Response();
        if(methodId == 1){
            List<Argument> args = request.getArgs();
            Argument arg0 = args.get(0);
            byte[] serializedCredential = arg0.getData();
            Credential credential = new Credential();
            credential.deserialize(serializedCredential);
            Token token = authenticationImpl.authenticate(credential);
            byte[] serializedToken = token.serialize();
            response.setStatusCode((byte) 100);
            response.setResponseBody(serializedToken);
        }
        return response;
    }
}
