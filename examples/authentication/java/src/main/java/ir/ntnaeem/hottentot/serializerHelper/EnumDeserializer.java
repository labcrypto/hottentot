package ir.ntnaeem.hottentot.serializerHelper;

public class EnumDeserializer {

    public static void deserialize(byte[] serializedEnumValue){
        short value = PDTDeserializer.getInt16(serializedEnumValue);
    }
}
