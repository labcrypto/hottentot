/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date:
 * Name:
 * Description:
 ******************************************************************/
package ir.ntnaeem.hottentot.examples.listtest.hotgen;

import ir.ntnaeem.hottentot.serializerHelper.DataLengthByteArrayMaker;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import ir.ntnaeem.hottentot.serializerHelper.ByteArrayToInteger;
import ir.ntnaeem.hottentot.type.*;

public class SerializableBoolList {

  private List<Boolean> boolList;

  public SerializableBoolList() {
    boolList = new ArrayList<Boolean>();
  }

  public List<Boolean> getBoolList() {
    return boolList;
  }

  public void setBoolList(List<Boolean> boolList) {
    this.boolList = boolList;
  }

  public byte[] serialize() {
    if (boolList.size() != 0) {
      int counter = 0;
      int dataLength = 0;
      //calculate serializedboolListLength
      for (Boolean bool : boolList) {
        _Boolean _Boolean = new _Boolean( bool );
        byte[] serializedBool = _Boolean.serialize();
        byte[] boolLengthByteArray =
          DataLengthByteArrayMaker.getByteArray(serializedBool.length);
        dataLength += boolLengthByteArray.length + serializedBool.length;
      }
      byte[] serializedBoolList = new byte[dataLength];
      for (Boolean bool : boolList) {
        _Boolean _Boolean = new _Boolean( bool );
        byte[] serializedBool = _Boolean.serialize();
        int serializedBoolLength = serializedBool.length;
        byte[] boolLengthByteArray =
          DataLengthByteArrayMaker.getByteArray(serializedBoolLength);
        System.arraycopy(boolLengthByteArray, 0, serializedBoolList, counter, boolLengthByteArray.length);
        counter += boolLengthByteArray.length;
        System.arraycopy(serializedBool, 0, serializedBoolList, counter, serializedBool.length);
        counter += serializedBool.length;
      }
      return serializedBoolList;
    }
    return new byte[0];
  }

  public byte[] serializeWithLength() {
    byte[] serializedBytes = serialize();
    byte[] dataLengthInBytes = DataLengthByteArrayMaker.getByteArray(serializedBytes.length);
    byte[] output = new byte[serializedBytes.length + dataLengthInBytes.length];
    int c = 0;
    for(int i = 0 ; i < dataLengthInBytes.length ; i++){
      output[c++] = dataLengthInBytes[i];
    }
    for(int i = 0 ; i < serializedBytes.length ; i++){
      output[c++] = serializedBytes[i];
    }
    return output;
  }

  public void deserialize(byte[] serializedBoolList) {
    if(serializedBoolList.length != 0){
      int counter = 0;
      int serializedBoolByteArrayLength = 0 ;
      while (true) {
        if (counter == serializedBoolList.length) {
          break;
        }
        int firstLengthByte = serializedBoolList[counter];
        int numOfByteForLength = 1;
        if ((firstLengthByte & 0x80) == 0) {
          serializedBoolByteArrayLength = serializedBoolList[counter];
        } else {
          counter++;
          numOfByteForLength = firstLengthByte & 0x0f;
          byte[] serializedBoolLengthByteArray = new byte[numOfByteForLength];
          int serializedDataWrapperLengthByteArrayCounter = 0;
          for (int i = counter; i < counter + numOfByteForLength; i++) {
            serializedBoolLengthByteArray[serializedDataWrapperLengthByteArrayCounter++] = serializedBoolList[i];
          }
          serializedBoolByteArrayLength = ByteArrayToInteger.getInt(serializedBoolLengthByteArray);
        }
        counter += numOfByteForLength;
        byte[] boolByteArray = new byte[serializedBoolByteArrayLength];
        int boolByteArrayCounter = 0;
        for (int i = counter; i < counter + serializedBoolByteArrayLength; i++) {
          boolByteArray[boolByteArrayCounter++] = serializedBoolList[i];
        }
        counter += serializedBoolByteArrayLength;
        _Boolean _Boolean = new _Boolean();
        _Boolean.deserialize(boolByteArray);
        boolList.add(_Boolean.getValue());
      }
    }
  }
}