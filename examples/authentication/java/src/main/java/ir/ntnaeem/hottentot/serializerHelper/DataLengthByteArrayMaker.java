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

import java.nio.ByteBuffer;


public class DataLengthByteArrayMaker {
    public static byte[] getByteArray(int dataLength) {
        byte[] byteArray;
        if (dataLength >= 0x80) {
            if (dataLength <= 0xff) {
                //ex 0x81 0xff
                byteArray = new byte[2];
                byteArray[0] = (byte) 0x81;
                byteArray[1] = (byte) dataLength;
            } else if (dataLength <= 0xffff) {
                //ex 0x82 0xff 0xff
                byteArray = new byte[3];
                byteArray[0] = (byte) 0x82;
                byte[] byteBuffer = ByteBuffer.allocate(2).putShort((short)dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
            } else if (dataLength <= 0xffffff) {
                //ex 0x83 0xff 0xff 0xff
                byteArray = new byte[5];
                byteArray[0] = (byte) 0x83;
                byte[] byteBuffer = ByteBuffer.allocate(4).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
                byteArray[3] = byteBuffer[2];
            } else {
                //ex 0x84 0xff 0xff 0xff 0xff
                byteArray = new byte[5];
                byteArray[0] = (byte) 0x84;
                byte[] byteBuffer = ByteBuffer.allocate(4).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
                byteArray[3] = byteBuffer[2];
                byteArray[4] = byteBuffer[3];
            }
        } else {
            //ex 0x7f
            byteArray = new byte[1];
            byteArray[0] = (byte) dataLength;
        }
        return byteArray;
    }
}
