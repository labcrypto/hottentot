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
import java.nio.ByteBuffer;
import java.util.Arrays;
import static java.lang.StrictMath.pow;

public class PDTSerializer {
  public static byte[] getData(byte[] bytes) {
    if(bytes == null){
      return new byte[]{0};
    }
//    byte[] concat = ArrayUtil.concat(DataLengthByteArrayMaker.getByteArray(bytes.length), bytes);
//    System.out.println(Arrays.toString(concat));
    return ArrayUtil.concat(DataLengthByteArrayMaker.getByteArray(bytes.length), bytes);
  }

  public static byte[] getString(String str) {
    byte[] strBytes =  ArrayUtil.concat(DataLengthByteArrayMaker.getByteArray(str.getBytes().length + 1), str.getBytes());
    return ArrayUtil.concat(strBytes , new byte[]{0});
  }

  public static byte[] getBool(boolean bool) {
    byte[] bytes = new byte[1];
    if (bool) {
      bytes[0] = 1;
    } else {
      bytes[0] = 0;
    }
    return bytes;
  }

  public static byte[] getInt8(byte number) {
    return new byte[]{number};
  }

  public static byte[] getUint8(byte number) {
    return new byte[]{number};
  }

  public static byte[] getInt16(short number) {
    return ByteBuffer.allocate(2).putShort(number).array();
  }

  public static byte[] getUint16(short number) {
    return ByteBuffer.allocate(2).putShort(number).array();
  }

  public static byte[] getInt32(int number){
    return ByteBuffer.allocate(4).putInt(number).array();
  }

  public static byte[] getUint32(int number){
    return ByteBuffer.allocate(4).putInt(number).array();
  }

  public static byte[] getInt64(long number) {
    return ByteBuffer.allocate(8).putLong(number).array();
  }

  public static byte[] getUint64(long number){
    return ByteBuffer.allocate(8).putLong(number).array();
  }
}
