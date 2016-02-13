package ir.ntnaeem.hottentot.type;

import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;

public class _Boolean {

  private boolean value;

  public _Boolean() {
  }

  public _Boolean(boolean value){
    this.value = value;
  }
  public boolean getValue() {
    return value;
  }

  public void setValue(boolean value) {
    this.value = value;
  }

  public byte[] serialize() {
    return PDTSerializer.getBool(value);
  }

  public void deserialize(byte[] serializedByteArray) {
    if (serializedByteArray.length != 0) {
      setValue(PDTDeserializer.getBool(serializedByteArray));
    }
  }
}
