package example.generatedBackup;

import ir.ntnaeem.hottentot.runtime.Argument;
import ir.ntnaeem.hottentot.runtime.Request;
import ir.ntnaeem.hottentot.runtime.RequestHandler;
import ir.ntnaeem.hottentot.runtime.Response;
import ir.ntnaeem.hottentot.runtime.Service;
import ir.ntnaeem.hottentot.runtime.exception.MethodNotSupportException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;

import java.util.List;

public class AuthenticationRequestHandler extends RequestHandler {
    public AuthenticationRequestHandler(Service service) {
        super(service);
    }
    @Override
    public Response handleRequest(Request request) throws TcpClientWriteException, TcpClientReadException, TcpClientConnectException, MethodNotSupportException {
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
			token = authenticationImpl.authenticate(credential);
			byte[] serializedToken = token.serialize();
			response.setStatusCode((byte) 100);
			response.setData(serializedToken);
			response.setLength(serializedToken.length + 1);
			return response;
		}
		throw new MethodNotSupportException("method id is incorrect");
    }
}
