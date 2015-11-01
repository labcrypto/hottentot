package runtime.service;


import runtime.Endpoint;
import runtime.ProtocolFactory;
import runtime.RequestHandler;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ServiceRuntime {

    private Map<Endpoint,List<Service>> serviceMap = new HashMap<Endpoint, List<Service>>();
    private Map<Endpoint , Map<Integer , RequestHandler>> requestHandlerMap = new HashMap<Endpoint, Map<Integer, RequestHandler>>();
    public void register(String host , int port , Service service){
        //TODO

        Endpoint endPoint = new Endpoint();
        endPoint.setHost(host);
        endPoint.setPort(port);


        if(serviceMap.containsKey(endPoint)){
            List<Service> serviceListInEndpoint = serviceMap.get(endPoint);
            //TODO search in service list for duplicate service registered
            serviceListInEndpoint.add(service);
            Map<Integer, RequestHandler> requestHandlerMapInEndpoint = requestHandlerMap.get(endPoint);
            requestHandlerMapInEndpoint.put(service.getServiceId() , service.getRequestHandler());
        }else{
            ArrayList<Service> serviceList = new ArrayList<Service>();
            serviceList.add(service);
            serviceMap.put(endPoint,serviceList);
            HashMap<Integer, RequestHandler> requestHandlers = new HashMap<Integer , RequestHandler>();
            requestHandlers.put(service.getServiceId() , service.getRequestHandler());
            requestHandlerMap.put(endPoint, requestHandlers);
        }

    }
    public void start() throws IOException {
        //TODO  ????!!!!

        for(Map.Entry<Endpoint , Map<Integer , RequestHandler> > entry : requestHandlerMap.entrySet()){
            Map<Integer, RequestHandler> requestHandlerMapInEndpoint = entry.getValue();
            Endpoint endpoint = entry.getKey();
            TcpServer tcpServer = TcpServerFactory.create(endpoint.getHost() , endpoint.getPort() , requestHandlerMapInEndpoint );
            tcpServer.bindAndStart();
            tcpServer.setProtocol(ProtocolFactory.create());
        }
//        for (ServiceInfo serviceInfo : servicePool){
//            TcpServer tcpServer = TcpServerFactory.create(serviceInfo);
//            tcpServer.bindAndStart();
//            tcpServer.setProtocol(ProtocolFactory.create());
//        }
    }
}
