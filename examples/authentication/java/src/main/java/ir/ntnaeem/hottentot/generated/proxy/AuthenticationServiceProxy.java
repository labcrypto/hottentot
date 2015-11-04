package ir.ntnaeem.hottentot.generated.proxy;


import ir.ntnaeem.hottentot.generated.Argument;
import ir.ntnaeem.hottentot.generated.Credential;
import ir.ntnaeem.hottentot.generated.Token;
import ir.ntnaeem.hottentot.runtime.*;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import ir.ntnaeem.hottentot.runtime.Proxy;
import ir.ntnaeem.hottentot.runtime.factory.ProtocolFactory;
import ir.ntnaeem.hottentot.runtime.factory.TcpClientFactory;

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


        //connect to ir.ntnaeem.hottentot.server
        TcpClient tcpClient = TcpClientFactory.create();
        tcpClient.connect(host, port);
        //serialize request according to HTNP


        Protocol protocol = ProtocolFactory.create();
        byte[] serializedRequest = protocol.serializeRequest(request);

        //send request
        tcpClient.write(serializedRequest);
        //read response from ir.ntnaeem.hottentot.server
        byte[] buffer = new byte[256];
        while (!protocol.IsResponseComplete()) {

            System.out.println("counter");
            byte[] dataChunkRead = tcpClient.read();
            protocol.processDataForResponse(dataChunkRead);
        }
        //deserialize token part of response
        Response response = protocol.getResponse();
        //close everything

        //deserialize token part from response
        Token token = null;


        //***********
        System.out.println(response);
        //*************
        if (response.getStatusCode() == -1) {
            //throw exception
        } else {
            token = new Token();
            token.deserialize(response.getData());
        }
        return token;
    }


    public void destroy() {
        //TODO
    }


}
