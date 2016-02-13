package ir.ntnaeem.hottentot.type;


import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;

public class _Int64 {
  private long value;

  public _Int64(long value) {
    this.value = value;
  }

  public _Int64() {
  }

  public long getValue() {
    return value;
  }

  public void setValue(long value) {
    this.value = value;
  }

  public byte[] serialize() {
    return PDTSerializer.getInt64(value);
  }

  public void deserialize(byte[] serializedByteArray) {
    if (serializedByteArray.length != 0) {
      setValue(PDTDeserializer.getInt64(serializedByteArray));
    }
  }
}
