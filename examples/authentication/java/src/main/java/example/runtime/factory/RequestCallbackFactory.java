package example.runtime.factory;

import example.runtime.DefaultRequestCallback;
import example.runtime.RequestCallback;
import example.runtime.RequestHandler;

import java.util.Map;


public class RequestCallbackFactory {
    public static RequestCallback create(Map<Integer,RequestHandler> requestHandlers){
        return new DefaultRequestCallback(requestHandlers);
    }
}
