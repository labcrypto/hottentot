package test;

import java.nio.ByteBuffer;


public class Test {
  public static void main(String[] args) {
    byte[] bytes = new byte[]{3,-21};
    int i = ByteBuffer.wrap(bytes).getShort();
    System.out.println(i);
  }
}
