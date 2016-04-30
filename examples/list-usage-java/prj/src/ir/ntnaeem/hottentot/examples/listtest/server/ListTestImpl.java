package ir.ntnaeem.hottentot.examples.listtest.server;

import ir.ntnaeem.hottentot.examples.listtest.hotgen.AbstractListTestService;
import ir.ntnaeem.hottentot.examples.listtest.hotgen.Message;

import java.util.ArrayList;
import java.util.List;

class ListTestImpl extends AbstractListTestService {
  @Override
  public void addNames(List<String> names) {
    System.out.println("------------------------");
    System.out.println("add names method call");
    for(String name : names){
      System.out.println(name);
    }
  }

  @Override
  public List<String> getNames() {
    System.out.println("------------------------");
    System.out.println("get names method call");
    ArrayList<String> names = new ArrayList<>();
    names.add("name-1");
    names.add("name-2");
    return names;
  }

  @Override
  public List<Message> getMessages() {
    System.out.println("------------------------");
    System.out.println("get messages method call");
    ArrayList<Message> messages = new ArrayList<>();
    Message message = new Message();
    message.setValue("msg1");
    Message message2 = new Message();
    message2.setValue("msg2");
    messages.add(message);
    messages.add(message2);
    return messages;
  }

  @Override
  public void addMessage(Message message) {
    System.out.println("------------------------");
    System.out.println("add message method call");
    System.out.println(message.getValue());
  }

  @Override
  public void addNumbers(List<Short> numbers) {
    System.out.println("------------------------");
    System.out.println("add numbers method call");
    for(Short number : numbers){
      System.out.println(number);
    }
  }
  //implementation
}