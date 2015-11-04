package ir.ntnaeem.hottentot.runtime.factory;

import ir.ntnaeem.hottentot.runtime.DefaultRequestCallback;
import ir.ntnaeem.hottentot.runtime.RequestCallBack;
import ir.ntnaeem.hottentot.runtime.RequestHandler;

import java.util.Map;


public class RequestCallbackFactory {
    public static RequestCallBack create(Map<Integer,RequestHandler> requestHandlers){
        return new DefaultRequestCallback(requestHandlers);
    }
}
