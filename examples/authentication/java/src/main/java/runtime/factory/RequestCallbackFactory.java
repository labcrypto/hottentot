package runtime.factory;

import runtime.DefaultRequestCallback;
import runtime.RequestCallBack;
import runtime.RequestHandler;

import java.util.Map;


public class RequestCallbackFactory {
    public static RequestCallBack create(Map<Integer,RequestHandler> requestHandlers){
        return new DefaultRequestCallback(requestHandlers);
    }
}
