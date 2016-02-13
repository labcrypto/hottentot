/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTAB_STRILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

package ir.ntnaeem.hottentot.runtime;

import ir.ntnaeem.hottentot.runtime.config.Config;
import ir.ntnaeem.hottentot.runtime.exception.HottentotRuntimeException;
import ir.ntnaeem.hottentot.runtime.factory.TcpServerFactory;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ServiceRuntime {

  //private Map<Endpoint, List<Service>> serviceMap = new HashMap<Endpoint, List<Service>>();
  private Map<Endpoint, Map<Long, RequestHandler>> endpoint_service_map = new HashMap<Endpoint, Map<Long, RequestHandler>>();
  private Map<Long , RequestHandler> serviceId_requestHandler_map = new HashMap<Long , RequestHandler>();

  public void register(String host, int port, Service service) {
    Endpoint endPoint = new Endpoint(host, port);
//    if (serviceMap.containsKey(endPoint)) {
//      List<Service> serviceListInEndpoint = serviceMap.get(endPoint);
//      //TODO search in service list for duplicate service registered
//      serviceListInEndpoint.add(service);
//      Map<Long, RequestHandler> requestHandlerMapInEndpoint = requestHandlerMap.get(endPoint);
//      requestHandlerMapInEndpoint.put(service.getServiceId(), service.makeRequestHandler());
//    } else {
    //ArrayList<Service> serviceList = new ArrayList<Service>();
    //serviceList.add(service);
    //serviceMap.put(endPoint, serviceList);

    serviceId_requestHandler_map.put(service.getServiceId(), service.makeRequestHandler());
    //

    endpoint_service_map.put(endPoint, serviceId_requestHandler_map);

  }

  public void start() {
    //System.out.println("size : " + endpoint_service_map.size());
    for (Map.Entry<Endpoint, Map<Long, RequestHandler>> entry : endpoint_service_map.entrySet()) {
      Endpoint endpoint = entry.getKey();
      Map<Long, RequestHandler> requestHandlerMapInEndpoint = entry.getValue();
      final TcpServer tcpServer = TcpServerFactory.create(endpoint.getHost(), endpoint.getPort(), requestHandlerMapInEndpoint);
      //make a thread for every endpoint
      new Thread(new Runnable() {
        @Override
        public void run() {
          try {
            tcpServer.bindAndStart();
          } catch (IOException e) {
            throw new HottentotRuntimeException(e);
          }
        }
      }).start();
    }
  }
}
