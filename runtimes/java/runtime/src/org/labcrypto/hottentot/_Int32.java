package org.labcrypto.hottentot;


import org.labcrypto.hottentot.helper.PDTDeserializer;
import org.labcrypto.hottentot.helper.PDTSerializer;

public class _Int32 {
  private int value;

  public _Int32(int value) {
    this.value = value;
  }

  public _Int32() {
  }

  public int getValue() {
    return value;
  }

  public void setValue(int value) {
    this.value = value;
  }

  public byte[] serialize() {
    return PDTSerializer.getInt32(value);
  }

  public void deserialize(byte[] serializedByteArray) {
    if (serializedByteArray.length != 0) {
      setValue(PDTDeserializer.getInt32(serializedByteArray));
    }
  }
}
