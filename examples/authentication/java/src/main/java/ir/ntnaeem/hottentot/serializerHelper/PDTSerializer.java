/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTAB_STRILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
package ir.ntnaeem.hottentot.serializerHelper;

import ir.ntnaeem.hottentot.runtime.helper.ArrayUtil;

import java.util.Arrays;

import static java.lang.StrictMath.pow;

public class PDTSerializer {
    public static byte[] getData(byte[] bytes) {
      return  ArrayUtil.concat(DataLengthByteArrayMaker.getByteArray(bytes.length), bytes);
    }
    public static byte[] getString(String str){
        return  ArrayUtil.concat(DataLengthByteArrayMaker.getByteArray(str.getBytes().length), str.getBytes());
    }
    public static byte getBool(boolean bool){
        byte b;
        if(bool){
            b = 1;
        }else{
            b = 0;
        }
        return b;
    }
    public static byte getInt8(short number){
        return (byte)number;
    }
    public static byte[] getInt16(short number){
        byte[] byteArray = new byte[2];
        short temp;
        for(short i = 0 ; i < byteArray.length ; i++){
            temp = (short) (number / pow(256,byteArray.length - i - 1));
            byteArray[i] = (byte)temp;
            number = (short) (number - (temp * pow(256,byteArray.length - i - 1)));
        }
        return byteArray;
    }

    public static byte[] getInt32(int number){
        byte[] byteArray = new byte[4];
        int temp;
        for(int i = 0 ; i < byteArray.length ; i++){
            temp = (int) (number / pow(256,byteArray.length - i - 1));
            byteArray[i] = (byte) temp;
            number = (int) (number - (temp * pow(256,byteArray.length - i - 1)));
        }
        return byteArray;
    }

    public static byte[] getInt64(long number){
        byte[] byteArray = new byte[8];
        long temp;
        for(short j = 0 ; j < byteArray.length ; j++) {
            temp = (long)(number / pow(256,byteArray.length - j - 1));
            byteArray[j] = (byte)temp;
            number = number - (long)(temp * pow(256,byteArray.length - j - 1));
        }
        return byteArray;
    }
}
