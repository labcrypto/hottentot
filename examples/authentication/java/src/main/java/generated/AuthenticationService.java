package generated;


import runtime.exception.TcpClientConnectException;
import runtime.exception.TcpClientReadException;
import runtime.exception.TcpClientWriteException;
import runtime.Service;

public interface AuthenticationService extends Service{
    Token authenticate(Credential credential) throws TcpClientConnectException, TcpClientWriteException, TcpClientReadException;
}
