package ir.ntnaeem.hottentot.runtime;

import ir.ntnaeem.hottentot.runtime.exception.HottentotRuntimeException;
import ir.ntnaeem.hottentot.runtime.factory.TcpServerFactory;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ServiceRuntime {

    private Map<Endpoint,List<Service>> serviceMap = new HashMap<Endpoint, List<Service>>();
    private Map<Endpoint , Map<Integer , RequestHandler>> requestHandlerMap = new HashMap<Endpoint, Map<Integer, RequestHandler>>();
    public void register(String host , int port , Service service){
        Endpoint endPoint = new Endpoint(host,port);
        if(serviceMap.containsKey(endPoint)){
            List<Service> serviceListInEndpoint = serviceMap.get(endPoint);
            //TODO search in service list for duplicate service registered
            serviceListInEndpoint.add(service);
            Map<Integer, RequestHandler> requestHandlerMapInEndpoint = requestHandlerMap.get(endPoint);
            requestHandlerMapInEndpoint.put(service.getServiceId() , service.makeRequestHandler());
        }else{
            ArrayList<Service> serviceList = new ArrayList<Service>();
            serviceList.add(service);
            serviceMap.put(endPoint,serviceList);
            HashMap<Integer, RequestHandler> requestHandlers = new HashMap<Integer , RequestHandler>();
            requestHandlers.put(service.getServiceId() , service.makeRequestHandler());
            requestHandlerMap.put(endPoint, requestHandlers);
        }
    }
    public void start(){
        for(Map.Entry<Endpoint , Map<Integer , RequestHandler> > entry : requestHandlerMap.entrySet()){
            Map<Integer, RequestHandler> requestHandlerMapInEndpoint = entry.getValue();
            Endpoint endpoint = entry.getKey();
            TcpServer tcpServer = TcpServerFactory.create(endpoint.getHost(), endpoint.getPort(), requestHandlerMapInEndpoint);
            try {
                tcpServer.bindAndStart();
            } catch (IOException e) {
                throw new HottentotRuntimeException(e);
            }
        }
        while(true);
    }
}
