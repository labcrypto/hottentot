package ir.ntnaeem.hottentot.runtime;


import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;

public interface TcpClient {
    void connect(String host, int port) throws TcpClientConnectException;
    void write(byte[] date) throws TcpClientWriteException;
    byte[] read() throws TcpClientReadException;
    void close();
}

