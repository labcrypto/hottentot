package ir.ntnaeem.hottentot.type;

import ir.ntnaeem.hottentot.serializerHelper.ByteArrayToInteger;
import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;

public class _Data {

  private byte[] value;

  public _Data() {
  }

  public _Data(byte[] value){
    this.value = value;
  }
  public byte[] getValue() {
    return value;
  }

  public void setValue(byte[] value) {
    this.value = value;
  }

  public byte[] serialize() {
    if(value == null) {
      return new byte[]{0};
    }
    return value;
  }

  public void deserialize(byte[] serializedByteArray) {
    if (serializedByteArray.length != 0) {
//      int counter = 0;
//      int dataLength = 0;
//      int numbersOfBytesForDataLength;
//      //value : bytes
//      dataLength = 0;
//      if ((serializedByteArray[counter] & 0x80) == 0) {
//        dataLength = serializedByteArray[counter++];
//      } else {
//        numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;
//        byte[] serializedByteArrayLength = new byte[numbersOfBytesForDataLength];
//        for (byte i = 0; i < numbersOfBytesForDataLength; i++) {
//          serializedByteArrayLength[i] = serializedByteArray[counter++];
//        }
//        dataLength = ByteArrayToInteger.getInt(serializedByteArrayLength);
//      }
//      byte[] valueByteArray = new byte[dataLength];
//      System.arraycopy(serializedByteArray, counter, valueByteArray, 0, dataLength);
//      counter += dataLength;
//      setValue(valueByteArray);
      setValue(serializedByteArray);
    }
  }
}
