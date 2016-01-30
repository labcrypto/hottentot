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
package server;

import hotgen.*;
import java.util.ArrayList;
import java.util.List;

public class TestServiceImpl extends AbstractTestService {
  public List<Token> auth(Credential credential) {
    Token token = new Token();
    System.out.println(credential);
    if(credential.getUsername().equals("a")) {
      token.setId((byte)1);
    }else{
      token.setId((byte)-1);
    }
    List<Token> tokenList = new ArrayList<Token>();
    tokenList.add(token);
    return tokenList;
  }

  public List<DataWrapper> test() {
    byte[] data = new byte[100000];
    for(int i = 0 ; i < 10000; i++) {
      data[i] = (byte)i;
    }
    DataWrapper dataWrapper = new DataWrapper();
    dataWrapper.setDigi(data);
    dataWrapper.setValue("ali");
//    //
//    byte[] data2 = new byte[100000];
//    for(int i = 0 ; i < 100000 ; i++){
//      data2[i] = (byte)i;
//    }
//    //byte[] data2 = new byte[]{1};
//    DataWrapper dataWrapper2 = new DataWrapper();
//    dataWrapper2.setValue("b");
//    dataWrapper2.setDigi(data2);
    //
    List<DataWrapper> dataWrapperList = new ArrayList<DataWrapper>();
    //
    DataWrapper dataWrapper2 = new DataWrapper();
    dataWrapperList.add(dataWrapper);
    dataWrapperList.add(dataWrapper2);
    return dataWrapperList;
  }

  public List<StringWrapper> test2() {
    List<StringWrapper> stringWrapperList = new ArrayList<StringWrapper>();
    //
    StringWrapper stringWrapper = new StringWrapper();
    String str = "";
    for(int i = 0 ; i < 256 ; i++){
      str += "b";
    }
    stringWrapper.setValue(str);
    stringWrapperList.add(stringWrapper);
    //
    StringWrapper stringWrapper2 = new StringWrapper();
    String str2 = "";
    for(int i = 0 ; i < 20 ; i++){
      str2 += "a";
    }
    stringWrapper2.setValue(str2);
    stringWrapperList.add(stringWrapper2);
    //
    return stringWrapperList;
  }

  public StringWrapper test3() {
    StringWrapper stringWrapper = new StringWrapper();
    String str = "";
    for(int i = 0 ; i < 100000 ; i++){
      str += "a";
    }

    stringWrapper.setValue(str);
    return stringWrapper;
  }

  public DataWrapper test4() {
    DataWrapper dataWrapper = new DataWrapper();
    byte[] bytes = new byte[256];
    for(int i = 0 ; i < 256 ; i++){
      bytes[i] = 1;
    }
    dataWrapper.setDigi(bytes);
    return dataWrapper;
  }

  @Override
  public DataWrapper test5(List<StringWrapper> inputList) {
    DataWrapper dataWrapper = new DataWrapper();
    if(inputList.size() == 2){
      dataWrapper.setDigi(new byte[]{0});
    }else{
      dataWrapper.setDigi(new byte[]{-1});
    }
    return dataWrapper;
  }

  public DataWrapper test6(List<DataWrapper> inputs) {
    return null;
  }

  public SampleStruct test7() {
    SampleStruct result = new SampleStruct();
    result.setStatus8((byte) -100);
    result.setStatus16((short) -1000);
    result.setStatus32(-10000);
    result.setStatus64(-100000);
    result.setUstatus8((byte) -100);
    result.setUstatus16((short) -1000);
    result.setUstatus32(-10000);
    result.setUstatus64(-100000);
    return result;
  }

  @Override
  public StringWrapper test8(StringWrapper str) {
    //
    StringWrapper stringWrapper = new StringWrapper();
    String strOut = "";
    for(int i = 0 ; i < 1000  ; i++) {
      strOut += "a";
    }
    stringWrapper.setValue(strOut);
    return stringWrapper;
  }

  @Override
  public Result test9(SampleStruct sample) {
    return null;
  }

}
