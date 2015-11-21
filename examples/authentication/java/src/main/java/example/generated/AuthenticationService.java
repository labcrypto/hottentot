package example.generated;


import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import ir.ntnaeem.hottentot.runtime.Service;

public interface AuthenticationService extends Service {
	public Token authenticate(Credential credential) throws Exception;
}
