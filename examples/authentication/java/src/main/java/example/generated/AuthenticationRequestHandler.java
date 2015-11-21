package example.generated;

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

	if(methodId == 1){
		List <Argument> args = request.getArgs();
		Argument arg0 = args.get(0);
		byte[] serializedCredential = arg0.getData();
		Credential credential = new Credential();
		credential.deserialize(serializedCredential);
		Token token = null;
		Response response = new Response();
		try{
			token = authenticationImpl.authenticate(credential);
			byte[] serializedToken = token.serialize();
			response.setStatusCode((byte) 100);
			response.setData(serializedToken);
			response.setLength(serializedToken.length + 1);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return response;
	}
        
        //TODO throw exception
        return null;
    }
}
