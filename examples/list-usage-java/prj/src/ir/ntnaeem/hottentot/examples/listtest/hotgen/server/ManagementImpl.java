package ir.ntnaeem.hottentot.examples.listtest.hotgen.server;

import ir.ntnaeem.hottentot.examples.listtest.hotgen.*;

import java.util.List;

class ManagementImpl extends AbstractManagementService {
  @Override
  public boolean isCrawlerIdValid(long crawlerId) {
    return false;
  }

  @Override
  public long startCrawler(Crawler crawler, String startURL, List<String> domainList) {
    return 0;
  }

  @Override
  public void stopCrawler(long crawlerId) {

  }

  @Override
  public void pauseCrawler(long crawlerId) {

  }

  @Override
  public void resumeCrawler(long crawlerId) {

  }

  @Override
  public List<Crawler> getCrawlers() {
    return null;
  }

  @Override
  public Crawler getCrawlerById(long crawlerId) {
    return null;
  }

  @Override
  public String getStartURL(long crawlerId) {
    return null;
  }

  @Override
  public List<String> getDomainList(long crawlerId) {
    return null;
  }
  //implementation
}