package example.server;

import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;

import java.lang.reflect.Array;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class Test {
  public static void main(String[] args) {
    int int32 = PDTDeserializer.getInt32(new byte[]{0,0,0,-1});
    byte[] sba = PDTSerializer.getInt32(-1);

    //int anInt = ByteBuffer.allocate(4).wrap(new byte[]{0, 0, 0, -1}).getInt();
    byte[] ba = ByteBuffer.allocate(4).putInt(-1).array();
    System.out.println(Arrays.toString(ba));
    int a = ByteBuffer.allocate(4).wrap(ba).getInt();
    System.out.println(a);


  }
}
