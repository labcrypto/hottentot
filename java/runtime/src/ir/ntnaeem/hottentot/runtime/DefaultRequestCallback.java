package ir.ntnaeem.hottentot.runtime;

import java.util.Map;

public class DefaultRequestCallback implements RequestCallback {

    private Map<Integer , RequestHandler> requestHandlers;
    public DefaultRequestCallback(Map<Integer,RequestHandler> requestHandlers) {
        this.requestHandlers = requestHandlers;
    }

    public Response onRequest(Request request){
        //TODO(ali)
        RequestHandler requestHandler = requestHandlers.get((int)request.getServiceId());
        return requestHandler.handleRequest(request);
    }
}
