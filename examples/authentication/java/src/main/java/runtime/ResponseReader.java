package runtime;


import runtime.exception.TcpClientReadException;

public class ResponseReader {

    private TcpClient tcpClient;
    public ResponseReader(TcpClient tcpClient) {
        this.tcpClient = tcpClient;
    }

    public Response read() throws TcpClientReadException {
        Protocol protocol = new ProtocolV1();
        byte[] serializedResponse;
        try {
            //System.out.println("-----" + tcpClient);
            serializedResponse = tcpClient.read();

        } catch (TcpClientReadException e) {
            throw e;
        }
        //System.out.println(serializedResponse);
        return protocol.deserializeResponse(serializedResponse);
    }
}
