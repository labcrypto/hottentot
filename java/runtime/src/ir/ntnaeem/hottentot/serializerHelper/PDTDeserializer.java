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

import com.sun.org.apache.xalan.internal.xsltc.dom.SortingIterator;
import java.nio.ByteBuffer;
import java.util.Arrays;

import static java.lang.StrictMath.pow;

public class PDTDeserializer {

  public static void main(String[] args) {
    String string = getString(new byte[]{97 , 98 , 99});
    String str = "س";
    byte[] bytes = str.getBytes();
  }

  public static String getFullString(byte[] bytes) {
    //TODO notice utf8 !
    int dataLength = 0;
    int counter = 0;
    if((bytes[0] & 0x80) == 0) {
      dataLength = bytes[counter++];
    }else {
      int numbersOfBytesForDataLength = bytes[counter++] & 0x0f;
      byte[] dataLengthByteArray = new byte[numbersOfBytesForDataLength];
      for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
        dataLengthByteArray[i] = bytes[counter++];
      }
      dataLength = ByteArrayToInteger.getInt(dataLengthByteArray);
    }
    byte[] valueByteArray = new byte[dataLength - 1];
    System.arraycopy(bytes,counter,valueByteArray,0,dataLength - 1);
    return new String(valueByteArray);
  }
  public static String getString(byte[] bytes) {
    byte[] realByteArray = new byte[bytes.length - 1];
    System.arraycopy(bytes,0,realByteArray,0,bytes.length - 1);
    return new String(realByteArray);
  }

  public static boolean getBool(byte[] bytes) {
    if (bytes[0] == 1) {
      return true;
    }
    return false;
  }

  public static byte[] getFullData(byte[] bytes) {
    int dataLength = 0;
    int counter = 0;
    if((bytes[0] & 0x80) == 0) {
      dataLength = bytes[counter++];
    }else {
      int numbersOfBytesForDataLength = bytes[counter++] & 0x0f;
      byte[] dataLengthByteArray = new byte[numbersOfBytesForDataLength];
      for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
        dataLengthByteArray[i] = bytes[counter++];
      }
      dataLength = ByteArrayToInteger.getInt(dataLengthByteArray);
    }
    byte[] valueByteArray = new byte[dataLength];
    for(int i = 0 ; i < dataLength ; i++){
      valueByteArray[i] = bytes[counter++];
    }
    return valueByteArray;
  }

  public static byte[] getData(byte[] bytes) {
    return bytes;
  }



  public static byte getInt8(byte[] bytes) {
    return bytes[0];
  }

  public static short getUint16(byte[] bytes) {
    short number = 0;
    for (byte i = 0; i < bytes.length; i++) {
      if (bytes[i] < 0) {
        number += pow(256, bytes.length - 1 - i) * (bytes[i] + 256);
      } else {
        number += pow(256, bytes.length - 1 - i) * bytes[i];
      }
    }
    return number;
  }


  public static short getInt16(byte[] bytes) {
    return  ByteBuffer.allocate(2).wrap(bytes).getShort();
  }

  public static int getUint32(byte[] bytes) {
    int number = 0;
    for (byte i = 0; i < bytes.length; i++) {
      if (bytes[i] < 0) {
        number += pow(256, bytes.length - 1 - i) * (bytes[i] + 256);
      } else {
        number += pow(256, bytes.length - 1 - i) * bytes[i];
      }
    }
    return number;
  }

  public static int getInt32(byte[] bytes) {
    return  ByteBuffer.allocate(4).wrap(bytes).getInt();
  }

  public static long getUint64(byte[] bytes) {
    long number = 0L;
    for (byte i = 0; i < bytes.length; i++) {
      if (bytes[i] < 0) {
        number += pow(256, bytes.length - 1 - i) * (bytes[i] + 256);
      } else {
        number += pow(256, bytes.length - 1 - i) * bytes[i];
      }
    }
    return number;
  }

  public static long getInt64(byte[] bytes) {
    return  ByteBuffer.allocate(8).wrap(bytes).getLong();
  }
}
