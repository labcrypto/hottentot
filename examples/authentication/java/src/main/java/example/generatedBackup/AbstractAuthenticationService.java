package example.generatedBackup;

import ir.ntnaeem.hottentot.runtime.RequestHandler;

public abstract class AbstractAuthenticationService implements AuthenticationService {	
	public RequestHandler makeRequestHandler() {
		return new AuthenticationRequestHandler(this);
	}
	public int getServiceId() {
        	return 1;
	}
}
