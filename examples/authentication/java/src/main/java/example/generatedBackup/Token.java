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

package example.generatedBackup;

import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;


import static java.lang.StrictMath.pow;

public class Token {
    private String value;
    private short id;
    public void setValue(String value) {
        this.value = value;
    }
    public String getValue() {
        return value;
    }
    public void setId(short id) {
        this.id = id;
    }
    public short getId() {
        return id;
    }
	
    public byte[] serialize() {
        byte[] serializedValue = PDTSerializer.getString(value);
        byte[] serializedId = PDTSerializer.getInt16(id);
        byte[] output = new byte[serializedValue.length + serializedId.length];
        int counter = 0;
        //use a loop for every property
        for (int i = 0; i < serializedValue.length; i++) {
            output[counter++] = serializedValue[i];
        }
        for (int i = 0; i < serializedId.length; i++) {
            output[counter++] = serializedId[i];
        }
        return output;
    }
    public void deserialize(byte[] serializedToken) {
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
}
