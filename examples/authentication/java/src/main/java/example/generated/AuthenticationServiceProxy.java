package example.generated;

import ir.ntnaeem.hottentot.runtime.Argument;
import ir.ntnaeem.hottentot.runtime.*;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import ir.ntnaeem.hottentot.runtime.Proxy;
import ir.ntnaeem.hottentot.runtime.factory.ProtocolFactory;
import ir.ntnaeem.hottentot.runtime.factory.TcpClientFactory;
import ir.ntnaeem.hottentot.runtime.protocol.Protocol;
import java.util.Arrays;

public class AuthenticationServiceProxy extends AbstractAuthenticationService implements Proxy {
	
	private String host;
	private int port;

	public AuthenticationServiceProxy(String host, int port) {
		this.host = host;
		this.port = port;
	}
	public Token authenticate(Credential credential) throws Exception { 
		//serialize credential
		byte[] serializedCredential = credential.serialize();

		//make request
		Request request = new Request();
		request.setServiceId((byte) 1);
		request.setMethodId((byte) 1);
		request.setArgumentCount((byte) 1);
		request.setType(Request.RequestType.InvokeStateless);
		Argument arg0 = new Argument();
		arg0.setDataLength(credential.serialize().length);
		arg0.setData(credential.serialize());
		request.addArgument(arg0);
		int dataLength = 0;
		//calculate data length for every argument
		//calulate credentialDataLength
		int credentialDataLength= serializedCredential.length;
		int credentialDataLengthByteArrayLength = 1;
		if (credentialDataLength >= 0x80) {
			if (credentialDataLength <= 0xff) {
				//ex 0x81 0xff
				credentialDataLengthByteArrayLength = 2;
			} else if (credentialDataLength <= 0xffff) {
				//ex 0x82 0xff 0xff
				credentialDataLengthByteArrayLength = 3;
			} else if (credentialDataLength <= 0xffffff) {
				//ex 0x83 0xff 0xff 0xff
				credentialDataLengthByteArrayLength = 4;
			}
		}
		dataLength += credentialDataLength + credentialDataLengthByteArrayLength;
		//
		request.setLength(4 + dataLength);
		//connect to server
		TcpClient tcpClient = TcpClientFactory.create();
		tcpClient.connect(host, port);
		//serialize request according to HTNP
		Protocol protocol = ProtocolFactory.create();
		byte[] serializedRequest = protocol.serializeRequest(request);
		//send request
		tcpClient.write(serializedRequest);
		//read response from server
		byte[] buffer = new byte[256];
		while (!protocol.IsResponseComplete()) {
			byte[] dataChunkRead = tcpClient.read();
			protocol.processDataForResponse(dataChunkRead);
		}
		//deserialize token part of response
		Response response = protocol.getResponse();
		//close everything
		//deserialize Tokenpart from response
		Token token= null;
		if (response.getStatusCode() == -1) {
			//throw exception
		} else {
			token= new Token();
			token.deserialize(response.getData());
		}
		return token;
	}

	public void destroy() {
        	//TODO
	}
}
