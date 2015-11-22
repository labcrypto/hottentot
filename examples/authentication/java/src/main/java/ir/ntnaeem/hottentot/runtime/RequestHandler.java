package ir.ntnaeem.hottentot.runtime;


import ir.ntnaeem.hottentot.runtime.exception.MethodNotSupportException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;

public abstract class RequestHandler {


    protected Service service;
    public RequestHandler(Service service) {
        this.service = service;
    }
    abstract public Response handleRequest(Request request) throws TcpClientWriteException, TcpClientReadException, TcpClientConnectException, MethodNotSupportException;
}
