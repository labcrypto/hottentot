package org.labcrypto.hottentot;

import org.labcrypto.hottentot.runtime.helper.ArrayUtil;
import org.labcrypto.hottentot.helper.PDTDeserializer;

public class _String {

  private String value;

  public _String() {
  }

  public _String(String value){
    this.value = value;
  }
  public String getValue() {
    return value;
  }

  public void setValue(String value) {
    this.value = value;
  }

  public byte[] serialize() {
    return ArrayUtil.concat(value.getBytes(), new byte[]{0});
  }

  public void deserialize(byte[] serializedByteArray) {
    if (serializedByteArray.length != 0) {
//      int counter = 0;
//      int dataLength = 0;
//      int numbersOfBytesForDataLength;
//      //value : String
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
//      setValue(PDTDeserializer.getString(valueByteArray));

      //
      setValue(PDTDeserializer.getString(serializedByteArray));

    }
  }
}
