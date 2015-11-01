package generated.proxy;


import generated.AuthenticationRequestHandler;
import generated.Credential;
import generated.Token;
import runtime.*;
import runtime.exception.TcpClientConnectException;
import runtime.exception.TcpClientReadException;
import runtime.exception.TcpClientWriteException;
import runtime.Proxy;

public class AuthenticationServiceProxy extends AbstractAuthenticationService implements Proxy {

    private String host;
    private int port;

    public AuthenticationServiceProxy(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public Token authenticate(Credential credential) throws TcpClientConnectException, TcpClientWriteException, TcpClientReadException {

        //serialize credential
        byte[] serializedCredential = credential.serialize();

        //make request
        Request request = new Request();
        request.setServiceId((byte) 1);
        request.setMethodId((byte) 1);
        request.setArgumentCount((byte) 1);
        request.setType(Request.RequestType.InvokeStateless);
        request.addArgument(new Argument(serializedCredential.length, serializedCredential));
        //connect to server
        TcpClient tcpClient = new DefaultTcpClient(); // TODO(ali) Use factory.
        tcpClient.connect(host, port);
        //write the request object
        RequestWriter requestWriter = new RequestWriter(tcpClient);
        requestWriter.write(request);
        //deserialize token part of response
        ResponseReader responseReader = new ResponseReader(tcpClient);
        Response response = responseReader.read();
        //close everything

        //deserialize token part from response
        Token token = null;
        if (response.getStatusCode() == -1) {
            //throw exception
        } else {
            byte[] responseBody = response.getResponseBody();
            token = new Token().deserialize(response.getResponseBody());
        }
        return token;
    }

    public void destroy() {
        //TODO
    }


}
