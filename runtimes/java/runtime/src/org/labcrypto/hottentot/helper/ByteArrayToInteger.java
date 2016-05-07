package org.labcrypto.hottentot.helper;


public class ByteArrayToInteger {
    public static int getInt(byte[] bytes){
        int output = 0;
        for(int i = 0 ; i < bytes.length ; i++){
            int c = 0;
            if(bytes[i] < 0){
                c = (256 + bytes[i]);
            }else{
                c = bytes[i];
            }
            output += c * Math.pow(256 , bytes.length - i - 1);
        }
        return output;
    }
}
