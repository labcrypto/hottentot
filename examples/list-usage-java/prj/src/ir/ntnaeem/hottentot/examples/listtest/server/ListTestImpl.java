package ir.ntnaeem.hottentot.examples.listtest.server;

import ir.ntnaeem.hottentot.examples.listtest.hotgen.AbstractListTestService;
import ir.ntnaeem.hottentot.examples.listtest.hotgen.MessageBox;
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
  public List<MessageBox> getMessages() {
    System.out.println("------------------------");
    System.out.println("get messages method call");
    ArrayList<MessageBox> messages = new ArrayList<>();
    MessageBox message = new MessageBox();
    message.setValue("msg1");
    MessageBox message2 = new MessageBox();
    message2.setValue("msg2");
    messages.add(message);
    messages.add(message2);
    return messages;
  }

  @Override
  public void addMessage(MessageBox messageBox) {
    System.out.println("------------------------");
    System.out.println("add message method call");
    System.out.println(messageBox.getValue());
    System.out.println(messageBox.getXList());
    System.out.println(messageBox.getYList());
    System.out.println(messageBox.getZList());
  }

  @Override
  public void addShortNumbers(List<Short> numbers) {
    System.out.println("------------------------");
    System.out.println("add numbers method call");
    for(Short number : numbers){
      System.out.println(number);
    }
  }

  @Override
  public void addByteNumbers(List<Byte> numbers) {
    System.out.println("------------------------");
    System.out.println("add byte numbers method call");
    for(Byte number : numbers){
      System.out.println(number);
    }
  }


  //implementation
}