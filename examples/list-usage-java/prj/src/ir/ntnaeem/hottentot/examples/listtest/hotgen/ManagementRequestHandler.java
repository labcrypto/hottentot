/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   
 ******************************************************************/
package ir.ntnaeem.hottentot.examples.listtest.hotgen;

import ir.ntnaeem.hottentot.runtime.Argument;
import ir.ntnaeem.hottentot.runtime.Request;
import ir.ntnaeem.hottentot.runtime.RequestHandler;
import ir.ntnaeem.hottentot.runtime.Response;
import ir.ntnaeem.hottentot.runtime.Service;
import ir.ntnaeem.hottentot.runtime.config.Config;
import ir.ntnaeem.hottentot.runtime.exception.MethodNotSupportException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;
import java.util.List;

public class ManagementRequestHandler extends RequestHandler {
  public ManagementRequestHandler(Service service) {
    super(service);
  }
  @Override
  public Response handleRequest(Request request) throws TcpClientWriteException, TcpClientReadException, TcpClientConnectException {
    long methodId = request.getMethodId();
    ManagementService managementImpl = (AbstractManagementService) service;
    if(methodId == 852340039L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawlerId = arg0.getData();
      long crawlerId = PDTDeserializer.getUint64(serializedCrawlerId);
      Response response = new Response();
      boolean result = managementImpl.isCrawlerIdValid(crawlerId);
      byte[] serializedResult = PDTSerializer.getBool( result );
      response.setStatusCode((byte) 0);
      response.setData(serializedResult);
      response.setLength(serializedResult.length + 1);
      return response;
    }
    if(methodId == 732023276L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawler = arg0.getData();
      Crawler crawler = new Crawler();
      crawler.deserialize(serializedCrawler);
      Argument arg1 = args.get(1);
      byte[] serializedStartURL = arg1.getData();
      String startURL = PDTDeserializer.getString(serializedStartURL);
      Argument arg2 = args.get(2);
      byte[] serializedDomainList = arg2.getData();
      SerializableStringList serializableStringList = new SerializableStringList();
      serializableStringList.deserialize( serializedDomainList);
      List<String> domainList = serializableStringList.getStringList();
      Response response = new Response();
      long result = managementImpl.startCrawler(crawler,startURL,domainList);
      byte[] serializedResult = PDTSerializer.getUint64( result );
      response.setStatusCode((byte) 0);
      response.setData(serializedResult);
      response.setLength(serializedResult.length + 1);
      return response;
    }
    if(methodId == 1177595769L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawlerId = arg0.getData();
      long crawlerId = PDTDeserializer.getUint64(serializedCrawlerId);
      Response response = new Response();
      managementImpl.stopCrawler(crawlerId);
      response.setStatusCode((byte) 0);
      response.setData(new byte[]{0});
      response.setLength(0);
      return response;
    }
    if(methodId == 1990011886L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawlerId = arg0.getData();
      long crawlerId = PDTDeserializer.getUint64(serializedCrawlerId);
      Response response = new Response();
      managementImpl.pauseCrawler(crawlerId);
      response.setStatusCode((byte) 0);
      response.setData(new byte[]{0});
      response.setLength(0);
      return response;
    }
    if(methodId == 1151769776L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawlerId = arg0.getData();
      long crawlerId = PDTDeserializer.getUint64(serializedCrawlerId);
      Response response = new Response();
      managementImpl.resumeCrawler(crawlerId);
      response.setStatusCode((byte) 0);
      response.setData(new byte[]{0});
      response.setLength(0);
      return response;
    }
    if(methodId == 2298290131L){
      List <Argument> args = request.getArgs();
      SerializableCrawlerList serializableCrawlerList = new SerializableCrawlerList();
      Response response = new Response();
      List<Crawler> crawlerList = managementImpl.getCrawlers();
      byte[] serializedCrawlerList;
      if(crawlerList == null){
        serializedCrawlerList  = new byte[0];
      }else{
        serializableCrawlerList.setCrawlerList(crawlerList);
        serializedCrawlerList = serializableCrawlerList.serialize();
      }
      response.setStatusCode((byte) 0);
      response.setData(serializedCrawlerList);
      response.setLength(serializedCrawlerList.length + 1);
      return response;
    }
    if(methodId == 3219824823L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawlerId = arg0.getData();
      long crawlerId = PDTDeserializer.getUint64(serializedCrawlerId);
      Crawler crawler = null;
      Response response = new Response();
      crawler = managementImpl.getCrawlerById(crawlerId);
      byte[] serializedCrawler;
      if(crawler == null){
        serializedCrawler  = new byte[0];
      }else{
      serializedCrawler = crawler.serialize();
      }
      response.setStatusCode((byte) 0);
      response.setData(serializedCrawler);
      response.setLength(serializedCrawler.length + 1);
      return response;
    }
    if(methodId == 2137106771L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawlerId = arg0.getData();
      long crawlerId = PDTDeserializer.getUint64(serializedCrawlerId);
      Response response = new Response();
      String result = managementImpl.getStartURL(crawlerId);
      byte[] serializedResult = PDTSerializer.getString( result );
      response.setStatusCode((byte) 0);
      response.setData(serializedResult);
      response.setLength(serializedResult.length + 1);
      return response;
    }
    if(methodId == 1975619138L){
      List <Argument> args = request.getArgs();
      Argument arg0 = args.get(0);
      byte[] serializedCrawlerId = arg0.getData();
      long crawlerId = PDTDeserializer.getUint64(serializedCrawlerId);
      SerializableStringList serializableStringList = new SerializableStringList();
      Response response = new Response();
      List<String> stringList = managementImpl.getDomainList(crawlerId);
      byte[] serializedStringList;
      if(stringList == null){
        serializedStringList  = new byte[0];
      }else{
        serializableStringList.setStringList(stringList);
        serializedStringList = serializableStringList.serialize();
      }
      response.setStatusCode((byte) 0);
      response.setData(serializedStringList);
      response.setLength(serializedStringList.length + 1);
      return response;
    }

    Response response = new Response();
    response.setStatusCode((byte) 255);
    response.setData(new byte[]{0});
    response.setLength(2);
    if(Config.isVerboseMode){
      System.out.println("WARN : method id is incorrect");
    }
    return response;
  }
}