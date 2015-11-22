package ir.ntnaeem.hottentot.runtime;


import ir.ntnaeem.hottentot.runtime.exception.MethodNotSupportException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;

public interface RequestCallback {
    Response onRequest(Request request) throws TcpClientReadException, TcpClientConnectException, TcpClientWriteException, MethodNotSupportException;
}
