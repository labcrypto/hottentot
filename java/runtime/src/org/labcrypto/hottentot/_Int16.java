package org.labcrypto.hottentot;

import org.labcrypto.hottentot.helper.PDTDeserializer;
import org.labcrypto.hottentot.helper.PDTSerializer;

public class _Int16 {
  private short value;

  public _Int16(short value) {
    this.value = value;
  }

  public _Int16() {
  }

  public short getValue() {
    return value;
  }

  public void setValue(short value) {
    this.value = value;
  }

  public byte[] serialize() {
    return PDTSerializer.getInt16(value);
  }

  public void deserialize(byte[] serializedByteArray) {
    if (serializedByteArray.length != 0) {
      setValue(PDTDeserializer.getInt16(serializedByteArray));
    }
  }
}
