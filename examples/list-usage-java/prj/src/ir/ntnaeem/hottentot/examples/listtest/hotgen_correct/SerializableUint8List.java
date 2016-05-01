/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date:
 * Name:
 * Description:
 ******************************************************************/
package ir.ntnaeem.hottentot.examples.listtest.hotgen_correct;

import ir.ntnaeem.hottentot.serializerHelper.DataLengthByteArrayMaker;
import java.util.ArrayList;
import java.util.List;
import ir.ntnaeem.hottentot.serializerHelper.ByteArrayToInteger;
import ir.ntnaeem.hottentot.type.*;

public class SerializableUint8List {

  private List<Byte> uint8List;

  public SerializableUint8List() {
    uint8List = new ArrayList<Byte>();
  }

  public List<Byte> getUint8List() {
    return uint8List;
  }

  public void setUint8List(List<Byte> uint8List) {
    this.uint8List = uint8List;
  }

  public byte[] serialize() {
    if (uint8List.size() != 0) {
      int counter = 0;
      int dataLength = 0;
      //calculate serializeduint8ListLength
      for (Byte uint8 : uint8List) {
        _Int8 _Int8 = new _Int8( uint8 );
        byte[] serializedUint8 = _Int8.serialize();
        byte[] uint8LengthByteArray =
          DataLengthByteArrayMaker.getByteArray(serializedUint8.length);
        dataLength += uint8LengthByteArray.length + serializedUint8.length;
      }
      byte[] serializedUint8List = new byte[dataLength];
      for (Byte uint8 : uint8List) {
        _Int8 _Int8 = new _Int8( uint8 );
        byte[] serializedUint8 = _Int8.serialize();
        int serializedUint8Length = serializedUint8.length;
        byte[] uint8LengthByteArray =
          DataLengthByteArrayMaker.getByteArray(serializedUint8Length);
        System.arraycopy(uint8LengthByteArray, 0, serializedUint8List, counter, uint8LengthByteArray.length);
        counter += uint8LengthByteArray.length;
        System.arraycopy(serializedUint8, 0, serializedUint8List, counter, serializedUint8.length);
        counter += serializedUint8.length;
      }
      return serializedUint8List;
    }
    return new byte[]{0};
  }

  public void deserialize(byte[] serializedUint8List) {
    if(serializedUint8List.length != 0){
      int counter = 0;
      int serializedUint8ByteArrayLength = 0 ;
      while (true) {
        if (counter == serializedUint8List.length) {
          break;
        }
        int firstLengthByte = serializedUint8List[counter];
        int numOfByteForLength = 1;
        if ((firstLengthByte & 0x80) == 0) {
          serializedUint8ByteArrayLength = serializedUint8List[counter];
        } else {
          counter++;
          numOfByteForLength = firstLengthByte & 0x0f;
          byte[] serializedUint8LengthByteArray = new byte[numOfByteForLength];
          int serializedDataWrapperLengthByteArrayCounter = 0;
          for (int i = counter; i < counter + numOfByteForLength; i++) {
            serializedUint8LengthByteArray[serializedDataWrapperLengthByteArrayCounter++] = serializedUint8List[i];
          }
          serializedUint8ByteArrayLength = ByteArrayToInteger.getInt(serializedUint8LengthByteArray);
        }
        counter += numOfByteForLength;
        byte[] uint8ByteArray = new byte[serializedUint8ByteArrayLength];
        int uint8ByteArrayCounter = 0;
        for (int i = counter; i < counter + serializedUint8ByteArrayLength; i++) {
          uint8ByteArray[uint8ByteArrayCounter++] = serializedUint8List[i];
        }
        counter += serializedUint8ByteArrayLength;
        _Int8 _Int8 = new _Int8();
        _Int8.deserialize(uint8ByteArray);
        uint8List.add(_Int8.getValue());
      }
    }
  }
}