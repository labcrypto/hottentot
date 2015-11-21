package example.runtime;


import example.runtime.exception.TcpClientConnectException;
import example.runtime.exception.TcpClientReadException;
import example.runtime.exception.TcpClientWriteException;

public interface TcpClient {
    void connect(String host , int port) throws TcpClientConnectException;
    void write(byte[] date) throws TcpClientWriteException;
    byte[] read() throws TcpClientReadException;
    void close();
}

