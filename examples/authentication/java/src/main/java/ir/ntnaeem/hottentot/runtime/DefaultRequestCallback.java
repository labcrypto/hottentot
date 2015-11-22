package ir.ntnaeem.hottentot.runtime;

import ir.ntnaeem.hottentot.runtime.exception.MethodNotSupportException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;

import java.util.Map;

public class DefaultRequestCallback implements RequestCallback {

    private Map<Integer , RequestHandler> requestHandlers;
    public DefaultRequestCallback(Map<Integer,RequestHandler> requestHandlers) {
        this.requestHandlers = requestHandlers;
    }

    public Response onRequest(Request request) throws TcpClientReadException, TcpClientConnectException, TcpClientWriteException, MethodNotSupportException {
        RequestHandler requestHandler = requestHandlers.get((int)request.getServiceId());
        return requestHandler.handleRequest(request);
    }
}
