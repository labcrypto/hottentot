package ir.ntnaeem.hottentot.examples.listtest.hotgen.server;

import ir.ntnaeem.hottentot.examples.listtest.hotgen.*;

import java.util.List;

class ListTestImpl extends AbstractListTestService {
  @Override
  public void addNames(List<String> names) {

  }

  @Override
  public List<String> getNames() {
    return null;
  }

  @Override
  public List<Message> getMessages() {
    return null;
  }

  @Override
  public void addMessage(Message message) {

  }

  @Override
  public void addNumbers(List<Short> numbers) {
    System.out.println(numbers.get(0));
    System.out.println(numbers.get(1));
  }
  //implementation
}