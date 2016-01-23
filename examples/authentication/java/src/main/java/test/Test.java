package test;

public class Test {
  public static void main(String[] args) {
    byte[] bytes = {-61, 83};
    System.out.println(256 + bytes[0]);
    System.out.println((byte)195);
    System.out.println((256 - 61) * 256 + 83);
    int output = java.nio.ByteBuffer.wrap(new byte[]{ -61 , 83}).getShort();
    System.out.println(output);
  }
}
