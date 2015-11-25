package example.generatedBackup;



import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;

import java.util.Arrays;

import static java.lang.StrictMath.pow;


public class Test {
    private String value;
    private short id;

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }

    public short getId() {
        return id;
    }

    public void setId(short id) {
        this.id = id;
    }

    public  void deserialize(byte[] serializedToken) {
        int counter = 0;

        //do for every property
        //value : string
        int dataLength = 0 ;
        int numbersOfBytesForDataLength;
        if(serializedToken[counter] < 0x80){
            dataLength = serializedToken[counter++];
        }else{
            numbersOfBytesForDataLength = serializedToken[counter++] & 0x0f;
            for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
                dataLength += pow(256, numbersOfBytesForDataLength - i - 1) * serializedToken[counter++];
            }
        }
        byte[] valueByteArray = new byte[dataLength];
        System.arraycopy(serializedToken,counter,valueByteArray,0,dataLength);
        counter += dataLength;
        setValue(PDTDeserializer.getString(valueByteArray));
        //id : int16
        byte[] idByteArray = new byte[2];
        for(int i = 0 ; i < 2 ; i++){
            idByteArray[i] = serializedToken[counter++];
        }
        setId(PDTDeserializer.getInt16(idByteArray));
    }

    public static void main(String[] args) {
        Test test = new Test();

        byte[] int32 = PDTSerializer.getInt32(1024);
        System.out.println(Arrays.toString(int32));
        int number = PDTDeserializer.getInt32(int32);
        System.out.println(number);

        byte[] bytes = new byte[]{3,97,98,99,-1,0};
        test.deserialize(bytes);
        //System.out.println(test.getValue());
        //System.out.println(test.getId());
    }
}
