package ir.ntnaeem.hottentot.serializerHelper;


import java.util.Arrays;

public class ByteArrayToInteger {
    public static int getInt(byte[] bytes){
        int output = 0;
//        if(bytes.length == 1){
//            output = bytes[0];
//        }else if(bytes.length == 2){
//            output = bytes[0] * 256  + bytes[1];
//        }else if(bytes.length == 3){
//            byte[] byteArrayWith4BytesLength = new byte[4];
//            byteArrayWith4BytesLength[0] = 0;
//            for(int i = 0 ; i < 3 ; i++){
//                byteArrayWith4BytesLength[i + 1] = bytes[i];
//            }
//            output = java.nio.ByteBuffer.wrap(byteArrayWith4BytesLength).getInt();
//        }else if(bytes.length == 4){
//            output = java.nio.ByteBuffer.wrap(bytes).getInt();
//        }
        System.out.println("bytes : " + Arrays.toString(bytes));
        for(int i = 0 ; i < bytes.length ; i++){
            int c = 0;
            if(bytes[i] < 0){
                c = (256 + bytes[i]);
                System.out.println("c" + c);
            }else{
                c = bytes[i];
            }
            output += c * Math.pow(256 , bytes.length - i - 1);
        }
        System.out.println("output  : " + output);
        return output;
    }
}
