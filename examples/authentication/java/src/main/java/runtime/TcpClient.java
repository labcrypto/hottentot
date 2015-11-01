package runtime;


import runtime.exception.TcpClientConnectException;
import runtime.exception.TcpClientReadException;
import runtime.exception.TcpClientWriteException;

import java.io.IOException;

public interface TcpClient {
    void connect(String host , int port) throws TcpClientConnectException;
    void write(byte[] date) throws TcpClientWriteException;
    byte[] read() throws TcpClientReadException;
    void close();
}

