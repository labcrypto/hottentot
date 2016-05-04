package org.labcrypto.hottentot.helper;

public class EnumDeserializer {

    public static void deserialize(byte[] serializedEnumValue){
        short value = PDTDeserializer.getInt16(serializedEnumValue);
    }
}
