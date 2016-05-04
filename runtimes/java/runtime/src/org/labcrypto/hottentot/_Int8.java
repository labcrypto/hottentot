package org.labcrypto.hottentot;


import org.labcrypto.hottentot.helper.PDTDeserializer;
import org.labcrypto.hottentot.helper.PDTSerializer;

public class _Int8 {
  private byte value;

  public _Int8(byte value) {
    this.value = value;
  }

  public _Int8() {
  }

  public byte getValue() {
    return value;
  }

  public void setValue(byte value) {
    this.value = value;
  }

  public byte[] serialize() {
    return PDTSerializer.getInt8(value);
  }

  public void deserialize(byte[] serializedByteArray) {
    if (serializedByteArray.length != 0) {
      setValue(PDTDeserializer.getInt8(serializedByteArray));
    }
  }
}
