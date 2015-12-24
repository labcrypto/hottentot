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

import static java.lang.StrictMath.pow;


public class PDTDeserializer {

  public static String getFullString(byte[] bytes) {
    //TODO notice utf8 !
    int dataLength = 0;
    int counter = 0;
    if((bytes[0] & 0x80) == 0) {
      dataLength = bytes[counter++];
    }else {
      int numbersOfBytesForDataLength = bytes[0] & 0x0f;
      for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
        dataLength += pow(256, numbersOfBytesForDataLength - i - 1) * bytes[counter++];
      }
    }
    byte[] valueByteArray = new byte[dataLength];
    System.arraycopy(bytes,counter,valueByteArray,0,dataLength);
    return new String(valueByteArray);
  }
  public static String getString(byte[] bytes){
    return new String(bytes);
  }

  public static boolean getBool(byte b) {
    if (b == 1) {
      return true;
    }
    return false;
  }

  public static byte getInt8(byte[] bytes) {
    return (bytes[0] < 0) ? (byte) (256 + bytes[0]) : bytes[0];
  }

  public static short getInt16(byte[] bytes) {
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

  public static int getInt32(byte[] bytes) {
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

  public static long getInt64(byte[] bytes) {
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
}
