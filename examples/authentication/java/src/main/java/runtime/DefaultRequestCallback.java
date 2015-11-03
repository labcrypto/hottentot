package runtime;




import java.util.Map;

public class DefaultRequestCallback implements RequestCallBack {

    private Map<Integer , RequestHandler> requestHandlers;
    public DefaultRequestCallback(Map<Integer,RequestHandler> requestHandlers) {
        this.requestHandlers = requestHandlers;
    }

    public Response onRequest(Request request){
        //TODO(ali)
        RequestHandler requestHandler = requestHandlers.get((int)request.getServiceId());
        System.out.println(request);
        return requestHandler.handleRequest(request);
    }
}
