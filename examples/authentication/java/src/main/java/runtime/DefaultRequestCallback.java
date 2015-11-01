package runtime;


import java.util.Map;

public class DefaultRequestCallback implements RequestCallBack {

    private Map<Integer , RequestHandler> requestHandlers;
    public DefaultRequestCallback(Map<Integer,RequestHandler> requestHandlers) {
        this.requestHandlers = requestHandlers;
    }

    public void onRequest(Request request) {
        //TODO(ali)
        RequestHandler requestHandler = requestHandlers.get((int)request.getServiceId());
        Response response = requestHandler.handleRequest(request);
    }
}
